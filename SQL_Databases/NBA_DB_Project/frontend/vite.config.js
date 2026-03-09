import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  server: {
  port: 3000,      // choose whatever port you want
  strictPort: true // prevents Vite from auto-switching
  }
})
