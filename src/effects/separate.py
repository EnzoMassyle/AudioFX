from spleeter.separator import Separator
from spleeter.audio.adapter import AudioAdapter


audio_loader = AudioAdapter.default()
separator = Separator('spleeter:2stems')
import sys
print(sys.executable)
def demix(samples, vocals):
    '''
    samples -> numpy array for audio samples, separated by channel
    vocals -> bool with 1 meaning we want to extract vocals, 0 to extract instrumental
    '''
    # stems = separator.separate(samples)
    # return stems.get("vocals") if vocals else stems.get("accompaniment")
    print("Hello from demix!")
    return samples

print("hello")