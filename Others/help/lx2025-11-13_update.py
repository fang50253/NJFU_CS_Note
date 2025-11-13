import numpy as np
import sounddevice as sd
import scipy.io.wavfile as wav
import os
from scipy.fft import fft
from scipy.signal import butter, lfilter
import matplotlib.pyplot as plt

# ====== Parameters ======
SAMPLE_RATE = 16000      # Sample rate
DURATION = 1.0           # Duration for each digit (seconds)
MULTI_DIGIT_DURATION = 6.0  # Duration for multiple digits (seconds)
DIGITS = list(map(str, range(10)))  # 0~9
VOICEBANK_DIR = "voicebank"

# ====== 1. Denoising Filter ======
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def denoise_signal(data, fs):
    b, a = butter_bandpass(300, 3400, fs, order=6)  # Voice frequency range
    return lfilter(b, a, data)

# ====== 2. Recording Functions ======
def record_digit(digit, duration=DURATION):
    print(f"Please speak the digit: {digit} ...")
    sd.wait()
    recording = sd.rec(int(duration * SAMPLE_RATE), samplerate=SAMPLE_RATE, channels=1, dtype='float32')
    sd.wait()
    print("Recording completed.")
    return recording.flatten()

def record_multiple_digits(duration=MULTI_DIGIT_DURATION):
    print(f"Please speak multiple digits (e.g., 012345) ...")
    print(f"Recording for {duration} seconds...")
    sd.wait()
    recording = sd.rec(int(duration * SAMPLE_RATE), samplerate=SAMPLE_RATE, channels=1, dtype='float32')
    sd.wait()
    print("Recording completed.")
    return recording.flatten()

# ====== 3. Feature Extraction (FFT Spectrum) ======
def extract_features(signal):
    # Denoising
    signal = denoise_signal(signal, SAMPLE_RATE)
    # Fourier Transform
    fft_spectrum = np.abs(fft(signal))
    # Take the first half of valid frequencies
    fft_spectrum = fft_spectrum[:len(fft_spectrum)//2]
    # Normalization
    fft_spectrum = fft_spectrum / np.linalg.norm(fft_spectrum)
    return fft_spectrum

# ====== 4. Voice Bank Construction ======
def build_voicebank():
    os.makedirs(VOICEBANK_DIR, exist_ok=True)
    print("Building voice bank. Each digit will be recorded once.")
    for d in DIGITS:
        signal = record_digit(d)
        features = extract_features(signal)
        np.save(os.path.join(VOICEBANK_DIR, f"{d}.npy"), features)
    print("Voice bank construction completed.")

# ====== 5. Speech Recognition Functions ======
def recognize_single_digit(signal):
    input_features = extract_features(signal)
    
    # Load voice bank and compare
    min_dist = float('inf')
    recognized_digit = None
    for d in DIGITS:
        stored_features = np.load(os.path.join(VOICEBANK_DIR, f"{d}.npy"))
        dist = np.linalg.norm(input_features - stored_features)
        if dist < min_dist:
            min_dist = dist
            recognized_digit = d
    
    return recognized_digit

def recognize_single_digit_mode():
    print("Single digit recognition mode:")
    signal = record_digit("?")
    recognized_digit = recognize_single_digit(signal)
    print(f"Recognition result: {recognized_digit}")
    return recognized_digit

def recognize_multiple_digits():
    print("Multiple digits recognition mode:")
    signal = record_multiple_digits()
    
    # Split the long recording into segments (each 1 second for one digit)
    segment_length = int(SAMPLE_RATE * DURATION)
    total_segments = len(signal) // segment_length
    
    recognized_digits = []
    
    for i in range(total_segments):
        start_idx = i * segment_length
        end_idx = start_idx + segment_length
        segment = signal[start_idx:end_idx]
        
        # Skip silent or very quiet segments
        if np.max(np.abs(segment)) < 0.01:  # Threshold for silence
            continue
            
        digit = recognize_single_digit(segment)
        if digit is not None:
            recognized_digits.append(digit)
    
    result = ''.join(recognized_digits)
    print(f"Recognition result: {result}")
    return result

# ====== Main Program ======
if __name__ == "__main__":
    print("=== Automatic Speech Recognition System ===")
    
    # Build voice bank if not exists
    if not os.path.exists(VOICEBANK_DIR):
        build_voicebank()
    
    while True:
        print("\nSelect mode:")
        print("1 - Single digit recognition")
        print("2 - Multiple digits recognition")
        print("3 - Exit")
        
        choice = input("Enter your choice (1/2/3): ").strip()
        
        if choice == '1':
            recognize_single_digit_mode()
        elif choice == '2':
            recognize_multiple_digits()
        elif choice == '3':
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")
        
        if choice in ['1', '2']:
            cont = input("Continue? (y/n): ").strip().lower()
            if cont != 'y':
                print("Goodbye!")
                break