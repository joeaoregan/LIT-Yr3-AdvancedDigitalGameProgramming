export class SoundManager {
  constructor() {
    this.sounds = new Map();
    this.music = new Map();
    this.currentMusic = null;
    this.musicEnabled = true;
    this.soundEnabled = true;
  }

  static getInstance() {
    if (!SoundManager.instance) {
      SoundManager.instance = new SoundManager();
    }
    return SoundManager.instance;
  }

  loadSound(id, src) {
    const audio = new Audio();
    audio.src = src;
    this.sounds.set(id, audio);
  }

  loadMusic(id, src) {
    const audio = new Audio();
    audio.src = src;
    audio.loop = true;
    this.music.set(id, audio);
  }

  playSound(id) {
    if (!this.soundEnabled) return;
    const sound = this.sounds.get(id);
    if (sound) {
      const clone = sound.cloneNode();
      clone.volume = 0.6;
      clone.play().catch(() => {});
    }
  }

  playMusic(id) {
    if (!this.musicEnabled) return;
    if (this.currentMusic) {
      this.currentMusic.pause();
      this.currentMusic.currentTime = 0;
    }
    const track = this.music.get(id);
    if (track) {
      this.currentMusic = track;
      track.volume = 0.5;
      track.play().catch(() => {});
    }
  }

  stopMusic() {
    if (this.currentMusic) {
      this.currentMusic.pause();
      this.currentMusic.currentTime = 0;
      this.currentMusic = null;
    }
  }

  toggleMusic() {
    this.musicEnabled = !this.musicEnabled;
    if (!this.musicEnabled) {
      this.stopMusic();
    }
    return this.musicEnabled;
  }

  toggleSound() {
    this.soundEnabled = !this.soundEnabled;
    return this.soundEnabled;
  }
}

export const TheSoundManager = SoundManager.getInstance();
