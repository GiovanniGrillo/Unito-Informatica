// client/src/App.tsx
import { Routes, Route } from 'react-router-dom'
import Header from './components/layout/Header'
import Footer from './components/layout/Footer'
import HomePage from './pages/HomePage'
import ServicesPage from './pages/ServicesPage'
import ProductsPage from './pages/ProductsPage'
import LoginPage from './pages/LoginPage'
import { AuthProvider } from './contexts/AuthContext'

// Import CSS files
import './App.css'
import './styles/reset.css'
import './styles/layout.css'
import './styles/style.css'
import './styles/header.css'
import './styles/footer.css'
import './styles/carousel.css'
import './styles/gallery.css'
import './styles/content.css'
import './styles/services-box.css'
import './styles/products.css'

function App() {
    return (
        <AuthProvider>
            <Header />
            <Routes>
                <Route path="/" element={<HomePage />} />
                <Route path="/services" element={<ServicesPage />} />
                <Route path="/products" element={<ProductsPage />} />
                <Route path="/login" element={<LoginPage />} />
            </Routes>
            <Footer />
        </AuthProvider>
    )
}

export default App