import numpy as np
import sounddevice as sd
import scipy.io.wavfile as wav
import os
from scipy.fft import fft
from scipy.signal import butter, lfilter
import matplotlib.pyplot as plt

# ====== 参数 ======
SAMPLE_RATE = 16000      # 采样率
DURATION = 1.0           # 每个数字持续时间（秒）
DIGITS = list(map(str, range(10)))  # 0~9
VOICEBANK_DIR = "voicebank"

# ====== 1. 降噪滤波函数 ======
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def denoise_signal(data, fs):
    b, a = butter_bandpass(300, 3400, fs, order=6)  # 语音频段
    return lfilter(b, a, data)

# ====== 2. 录音函数 ======
def record_digit(digit, duration=DURATION):
    print(f"请朗读数字 {digit} ...")
    sd.wait()
    recording = sd.rec(int(duration * SAMPLE_RATE), samplerate=SAMPLE_RATE, channels=1, dtype='float32')
    sd.wait()
    print("录音完成。")
    return recording.flatten()

# ====== 3. 特征提取（FFT频谱） ======
def extract_features(signal):
    # 降噪
    signal = denoise_signal(signal, SAMPLE_RATE)
    # 傅里叶变换
    fft_spectrum = np.abs(fft(signal))
    # 取前半部分有效频率
    fft_spectrum = fft_spectrum[:len(fft_spectrum)//2]
    # 归一化
    fft_spectrum = fft_spectrum / np.linalg.norm(fft_spectrum)
    return fft_spectrum

# ====== 4. 构建语音库 ======
def build_voicebank():
    os.makedirs(VOICEBANK_DIR, exist_ok=True)
    print("开始录制语音库，每个数字会录制一次。")
    for d in DIGITS:
        signal = record_digit(d)
        features = extract_features(signal)
        np.save(os.path.join(VOICEBANK_DIR, f"{d}.npy"), features)
    print("语音库构建完成。")

# ====== 5. 识别输入语音 ======
def recognize_digit():
    print("请读出一个数字进行识别：")
    signal = record_digit("?")
    input_features = extract_features(signal)
    
    # 加载语音库并比较
    min_dist = float('inf')
    recognized_digit = None
    for d in DIGITS:
        stored_features = np.load(os.path.join(VOICEBANK_DIR, f"{d}.npy"))
        dist = np.linalg.norm(input_features - stored_features)
        if dist < min_dist:
            min_dist = dist
            recognized_digit = d
    
    print(f"识别结果：{recognized_digit}")
    return recognized_digit

# ====== 主程序入口 ======
if __name__ == "__main__":
    print("=== 自动语音识别系统 ===")
    if not os.path.exists(VOICEBANK_DIR):
        build_voicebank()
    while True:
        recognize_digit()
        cont = input("继续识别？(y/n): ")
        if cont.lower() != 'y':
            break