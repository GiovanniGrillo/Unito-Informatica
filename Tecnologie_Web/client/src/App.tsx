import { Routes, Route } from 'react-router-dom';
import Header from './components/layout/Header';
import Footer from './components/layout/Footer';
import HomePage from './pages/HomePage';
import ServicesPage from './pages/ServicesPage';
import ProductsPage from './pages/ProductsPage';
import LoginPage from './pages/LoginPage';
import { AuthProvider } from './contexts/AuthContext';
import { CartProvider } from './contexts/CartContext';
import Contacts from "./pages/Contacts.tsx";
import NotFoundPage from './pages/NotFoundPage';

import Cart from './components/features/Cart';
// Import CSS files
import './styles/global.css';
import './styles/header.css';
import './styles/footer.css';
import './styles/carousel.css';
import './styles/gallery.css';
import './styles/content.css';
import './styles/services-box.css';
import './styles/products.css';
import './styles/cart.css';

function App() {
    return (
        <AuthProvider>
            <CartProvider>
                <div className="app-container">
                    <Header />
                    <Cart />
                    <div className="main-content">
                        <Routes>
                            <Route path="/" element={<HomePage />} />
                            <Route path="/services" element={<ServicesPage />} />
                            <Route path="/products" element={<ProductsPage />} />
                            <Route path="/login" element={<LoginPage />} />
                            <Route path="/contacts" element={<Contacts/>} />
                            <Route path="*" element={<NotFoundPage />} />
                        </Routes>
                    </div>
                    <Footer />
                </div>
            </CartProvider>
        </AuthProvider>
    );
}

export default App;
