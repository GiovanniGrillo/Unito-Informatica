import React from 'react'
import ReactDOM from 'react-dom/client'
import 'bootstrap/dist/css/bootstrap.min.css'
import './assets/styles/reset.css'
import './assets/styles/layout.css'
import './assets/styles/header.css'
import './assets/styles/content.css'
import './assets/styles/footer.css'
import './assets/styles/gallery.css'
import './assets/styles/bootstrap-carousel.css'
import './assets/styles/services-box.css'
import App from './App'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)