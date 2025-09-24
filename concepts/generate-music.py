#!/usr/bin/env python3
"""
MIDI to XM (Extended Module) Converter
Converts MIDI files to XM tracker format without samples
Each MIDI channel gets its own instrument for later sample assignment
"""

import struct
import os
import sys
from pathlib import Path
from typing import List, Dict, Tuple, Optional, Set
import mido
from collections import defaultdict


class XMInstrument:
    """Represents an XM instrument with samples"""

    def __init__(self, name: str = ""):
        self.name = name[:22].ljust(22, "\0")
        self.samples = []
        self.sample_map = [0] * 96  # Note -> Sample mapping (all map to sample 0)
        self.volume_envelope = []
        self.panning_envelope = []


class XMSample:
    """Represents an XM sample"""

    def __init__(self, name: str = ""):
        self.data = b"\x00"  # Single zero byte instead of empty
        self.name = name[:22].ljust(22, "\0")
        self.length = 1  # Minimum length of 1
        self.loop_start = 0
        self.loop_length = 0
        self.volume = 64
        self.finetune = 0
        self.type = 0  # 0=8bit, 16=16bit
        self.panning = 128
        self.relative_note = 0


class XMPattern:
    """Represents an XM pattern"""

    def __init__(self, rows: int = 64):
        self.rows = rows
        self.data = []  # List of pattern data


class XMModule:
    """XM Module file structure"""

    def __init__(self):
        self.name = "Untitled"
        self.tracker_name = "MIDI2XM Converter"
        self.version = 0x0104  # XM version 1.04
        self.header_size = 276
        self.song_length = 1
        self.restart_pos = 0
        self.channels = 32  # Increased to 32 to accommodate more MIDI channels
        self.patterns = []
        self.instruments = []
        self.speed = 6  # Ticks per row (XM "speed")
        self.bpm = 125  # Default BPM
        self.pattern_order = []
        self.freq_table = 0  # 0=Amiga, 1=Linear

    def write(self, filename: str):
        """Write XM file"""
        with open(filename, "wb") as f:
            # Write header
            f.write(b"Extended Module: ")
            f.write(self.name[:20].encode("latin-1").ljust(20, b"\0"))
            f.write(b"\x1a")
            f.write(self.tracker_name[:20].encode("latin-1").ljust(20, b"\0"))
            f.write(struct.pack("<H", self.version))
            f.write(struct.pack("<I", self.header_size))
            f.write(struct.pack("<H", self.song_length))
            f.write(struct.pack("<H", self.restart_pos))
            f.write(struct.pack("<H", self.channels))
            f.write(struct.pack("<H", len(self.patterns)))
            f.write(struct.pack("<H", len(self.instruments)))
            f.write(struct.pack("<H", self.freq_table))
            f.write(struct.pack("<H", self.speed))
            f.write(struct.pack("<H", self.bpm))

            # Pattern order table
            for i in range(256):
                if i < len(self.pattern_order):
                    f.write(struct.pack("B", self.pattern_order[i]))
                else:
                    f.write(b"\x00")

            # Write patterns
            for pattern in self.patterns:
                self._write_pattern(f, pattern)

            # Write instruments
            for instrument in self.instruments:
                self._write_instrument(f, instrument)

    def _write_pattern(self, f, pattern: XMPattern):
        """Write pattern data"""
        # Pattern header
        f.write(struct.pack("<I", 9))  # Header length
        f.write(struct.pack("B", 0))  # Packing type
        f.write(struct.pack("<H", pattern.rows))

        # Calculate packed data size
        packed_data = self._pack_pattern_data(pattern)
        f.write(struct.pack("<H", len(packed_data)))
        f.write(packed_data)

    def _pack_pattern_data(self, pattern: XMPattern) -> bytes:
        """Pack pattern data using XM compression"""
        packed = bytearray()

        for row in pattern.data:
            # Ensure we have data for all channels
            for ch in range(self.channels):
                if ch < len(row) and row[ch] is not None:
                    note, inst, vol, eff, param = row[ch]

                    # Determine what to include
                    flags = 0
                    if note != 0:
                        flags |= 0x01
                    if inst != 0:
                        flags |= 0x02
                    if vol != 0:
                        flags |= 0x04
                    if eff != 0:
                        flags |= 0x08
                    if param != 0:
                        flags |= 0x10

                    if flags == 0:
                        # Empty, write compressed empty note
                        packed.append(0x80)
                    else:
                        # Write data
                        if flags != 0x1F:  # Use compression
                            packed.append(flags | 0x80)
                        else:
                            # All fields present
                            packed.extend([note, inst, vol, eff, param])
                            continue

                        if note != 0:
                            packed.append(note)
                        if inst != 0:
                            packed.append(inst)
                        if vol != 0:
                            packed.append(vol)
                        if eff != 0:
                            packed.append(eff)
                        if param != 0:
                            packed.append(param)
                else:
                    # Empty channel
                    packed.append(0x80)

        return bytes(packed)

    def _write_instrument(self, f, instrument: XMInstrument):
        """Write instrument data"""
        # Always write full instrument with sample
        inst_size = 263

        # Instrument header
        f.write(struct.pack("<I", inst_size))
        f.write(instrument.name.encode("latin-1"))
        f.write(struct.pack("B", 0))  # Type
        f.write(struct.pack("<H", 1))  # Always 1 sample

        # Sample header size
        f.write(struct.pack("<I", 40))

        # Sample number for all notes (all map to sample 0)
        for i in range(96):
            f.write(struct.pack("B", 0))

        # Volume envelope points (12 points, 2 bytes each)
        for i in range(12):
            f.write(struct.pack("<HH", 0, 64))  # Position, Value

        # Panning envelope points (12 points, 2 bytes each)
        for i in range(12):
            f.write(struct.pack("<HH", 0, 32))  # Position, Value

        # Number of envelope points
        f.write(struct.pack("B", 0))  # Vol points
        f.write(struct.pack("B", 0))  # Pan points

        # Envelope sustain points
        f.write(struct.pack("B", 0))  # Vol sustain
        f.write(struct.pack("B", 0))  # Vol loop start
        f.write(struct.pack("B", 0))  # Vol loop end
        f.write(struct.pack("B", 0))  # Pan sustain
        f.write(struct.pack("B", 0))  # Pan loop start
        f.write(struct.pack("B", 0))  # Pan loop end

        # Volume/panning type
        f.write(struct.pack("B", 0))  # Volume type
        f.write(struct.pack("B", 0))  # Panning type

        # Vibrato
        f.write(struct.pack("B", 0))  # Vibrato type
        f.write(struct.pack("B", 0))  # Vibrato sweep
        f.write(struct.pack("B", 0))  # Vibrato depth
        f.write(struct.pack("B", 0))  # Vibrato rate

        # Volume fadeout
        f.write(struct.pack("<H", 0))

        # Reserved
        f.write(struct.pack("<H", 0))

        # Write sample header
        sample = instrument.samples[0] if instrument.samples else XMSample()
        self._write_sample_header(f, sample)

        # Write minimal sample data
        f.write(sample.data)

    def _write_sample_header(self, f, sample: XMSample):
        """Write sample header"""
        f.write(struct.pack("<I", sample.length))
        f.write(struct.pack("<I", sample.loop_start))
        f.write(struct.pack("<I", sample.loop_length))
        f.write(struct.pack("B", sample.volume))
        f.write(struct.pack("b", sample.finetune))
        f.write(struct.pack("B", sample.type))
        f.write(struct.pack("B", sample.panning))
        f.write(struct.pack("b", sample.relative_note))
        f.write(struct.pack("B", 0))  # Reserved
        f.write(sample.name.encode("latin-1"))


class MidiToXMConverter:
    """Main converter class"""

    def __init__(self, rows_per_beat: int = 4):
        self.rows_per_beat = rows_per_beat  # Resolution: 4=16th notes, 8=32nd notes

    def convert(self, midi_file: str, output_file: str, target_bpm: int = 125):
        """Convert MIDI file to XM format"""
        # Load MIDI file
        mid = mido.MidiFile(midi_file)

        # Create XM module
        xm = XMModule()
        xm.name = Path(midi_file).stem

        # Convert MIDI to patterns
        patterns, channel_mapping, tempo_bpm = self._convert_midi_to_patterns(mid)

        # Set tempo/speed from MIDI
        xm.speed, _ = tempo_bpm
        xm.bpm = target_bpm  # Use the target BPM

        # Create instruments for all used channels
        # Always create at least 16 instruments for compatibility
        max_instruments = max(16, len(channel_mapping))
        for i in range(max_instruments):
            if i in channel_mapping.values():
                # Find which MIDI channel this maps to
                midi_channel = [k for k, v in channel_mapping.items() if v == i][0]
                instrument = self._create_empty_instrument(midi_channel, i)
            else:
                # Create dummy instrument
                instrument = self._create_empty_instrument(-1, i)
            xm.instruments.append(instrument)

        # Add patterns to module
        xm.patterns = patterns
        xm.pattern_order = list(range(len(patterns)))
        xm.song_length = len(patterns)

        # Write XM file
        xm.write(output_file)
        print(f"Converted {midi_file} to {output_file}")
        print(f"Created {max_instruments} instruments")
        print(f"MIDI channels mapped to XM tracks: {channel_mapping}")
        print(f"XM Speed: {xm.speed}, BPM: {xm.bpm}")

    def _convert_midi_to_patterns(
        self, mid: mido.MidiFile
    ) -> Tuple[List[XMPattern], Dict[int, int], Tuple[int, int]]:
        """Convert MIDI to XM patterns"""
        # Extract tempo from MIDI
        midi_tempo = 500000  # Default 120 BPM in microseconds per quarter note

        # Find tempo changes
        for track in mid.tracks:
            for msg in track:
                if msg.type == "set_tempo":
                    midi_tempo = msg.tempo
                    break

        # Convert MIDI tempo to XM BPM
        midi_bpm = 60000000 / midi_tempo

        # XM timing calculation
        xm_speed = 6  # Standard speed

        # Calculate XM BPM to match MIDI timing
        rows_per_minute = midi_bpm * self.rows_per_beat
        xm_bpm = int(rows_per_minute * xm_speed / 2.5)

        # Clamp BPM to valid range (32-255)
        xm_bpm = max(32, min(255, xm_bpm))

        print(f"MIDI BPM: {midi_bpm:.1f} -> XM Speed: {xm_speed}, BPM: {xm_bpm}")

        # Calculate ticks per row for MIDI conversion
        ticks_per_beat = mid.ticks_per_beat
        ticks_per_row = max(1, ticks_per_beat // self.rows_per_beat)

        # Track state - tracking all notes
        all_notes = {}  # channel -> list of (note, velocity, start_time, end_time)
        channels_used = set()

        # First pass: collect all note events
        for track in mid.tracks:
            track_time = 0
            active_notes = {}  # note -> (velocity, start_time)
            
            for msg in track:
                track_time += msg.time
                
                if hasattr(msg, 'channel'):
                    if msg.type == "note_on" and msg.velocity > 0:
                        channels_used.add(msg.channel)
                        active_notes[msg.note] = (msg.velocity, track_time)
                        
                    elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
                        if msg.note in active_notes:
                            velocity, start_time = active_notes[msg.note]
                            if msg.channel not in all_notes:
                                all_notes[msg.channel] = []
                            all_notes[msg.channel].append((msg.note, velocity, start_time, track_time))
                            del active_notes[msg.note]
            
            # Handle any remaining active notes
            for note, (velocity, start_time) in active_notes.items():
                # Find channel for this note
                for channel in channels_used:
                    if channel not in all_notes:
                        all_notes[channel] = []
                    # Assume note extends to end of track
                    all_notes[channel].append((note, velocity, start_time, track_time))
                    break

        # Create channel mapping (MIDI channel -> XM track)
        channel_mapping = {}
        xm_track = 0
        for midi_channel in sorted(channels_used):
            channel_mapping[midi_channel] = xm_track
            xm_track += 1

        # Second pass: create pattern data
        max_time = 0
        for channel_notes in all_notes.values():
            for _, _, _, end_time in channel_notes:
                max_time = max(max_time, end_time)

        max_row = (max_time // ticks_per_row) + 1
        
        # Initialize pattern data
        rows_data = []
        for row in range(max_row + 1):
            rows_data.append([None] * 32)  # 32 channels max

        # Place notes in pattern
        for midi_channel, notes in all_notes.items():
            xm_track = channel_mapping.get(midi_channel, 0)
            
            # Sort notes by start time
            notes.sort(key=lambda x: x[2])
            
            for note, velocity, start_time, end_time in notes:
                start_row = start_time // ticks_per_row
                end_row = end_time // ticks_per_row
                
                # Note on
                xm_note = self._midi_note_to_xm(note)
                xm_inst = xm_track + 1  # Instrument number = track + 1
                xm_vol = 0x10 + min(64, velocity >> 1)  # Volume column (0x10-0x50)
                
                if start_row < len(rows_data):
                    rows_data[start_row][xm_track] = (xm_note, xm_inst, xm_vol, 0, 0)
                
                # Note off
                if end_row < len(rows_data) and end_row != start_row:
                    # Only add note off if there's not already a note there
                    if rows_data[end_row][xm_track] is None:
                        rows_data[end_row][xm_track] = (97, 0, 0, 0, 0)  # Note off

        # Create patterns
        patterns = []
        rows_per_pattern = 64
        pattern_data = []

        for i, row_data in enumerate(rows_data):
            pattern_data.append(row_data)
            
            if (i + 1) % rows_per_pattern == 0:
                pattern = XMPattern(rows_per_pattern)
                pattern.data = pattern_data
                patterns.append(pattern)
                pattern_data = []

        # Add remaining rows
        if pattern_data:
            # Pad to multiple of 16 rows for better compatibility
            while len(pattern_data) % 16 != 0:
                pattern_data.append([None] * 32)
            
            pattern = XMPattern(len(pattern_data))
            pattern.data = pattern_data
            patterns.append(pattern)

        # Ensure we have at least one pattern
        if not patterns:
            pattern = XMPattern(64)
            pattern.data = [[None] * 32 for _ in range(64)]
            patterns.append(pattern)

        return patterns, channel_mapping, (xm_speed, xm_bpm)

    def _midi_note_to_xm(self, midi_note: int) -> int:
        """Convert MIDI note to XM note"""
        # XM notes: 1-96 (C-0 to B-7), 97=off
        # MIDI notes: 0-127 (C-1 to G9)
        # Map MIDI C4 (60) to XM C-4 (49)
        xm_note = midi_note - 11
        return max(1, min(96, xm_note))

    def _create_empty_instrument(self, channel: int, index: int) -> XMInstrument:
        """Create empty XM instrument for a MIDI channel"""
        if channel >= 0:
            instrument = XMInstrument(f"Channel {channel + 1:02d}")
        else:
            instrument = XMInstrument(f"Empty {index + 1:02d}")
        
        # Create one minimal sample
        sample = XMSample(f"Sample {index + 1:02d}")
        instrument.samples.append(sample)
        
        # All notes map to sample 0
        instrument.sample_map = [0] * 96
        
        return instrument

for file in os.listdir("midi"):

    if ".mid" in file:
        print(file)

        midi_file = "midi/" + file
        output_file = "temp/" + file.replace(".mid", ".midi").replace(".midi", ".xm")
        rows_per_beat = int(sys.argv[3]) if len(sys.argv) > 3 else 4
        target_bpm = int(sys.argv[4]) if len(sys.argv) > 4 else 125

        if not os.path.exists(midi_file):
            print(f"Error: MIDI file '{midi_file}' not found")
            sys.exit(1)

        # Create converter and convert
        converter = MidiToXMConverter(rows_per_beat)
        converter.convert(midi_file, output_file, target_bpm)