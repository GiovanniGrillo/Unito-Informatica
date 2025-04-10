import React from 'react';
import { Link } from "react-router-dom";
import { useAuth } from '../../contexts/AuthContext';
import { useCart } from '../../contexts/CartContext';


const Header: React.FC = () => {
    const { user, isAuthenticated, logout, isAdmin } = useAuth();
    const { toggleCart, getTotalItems } = useCart();

    // Funzione per lo scroll smooth alle sezioni
    return (
        <header>
            <div id="social-icons">
                <a href="https://www.facebook.com" className="social-icon" target="_blank" rel="noopener noreferrer">
                    <img src="/img/facebook_logo.svg" alt="Facebook" />
                </a>
                <a href="https://www.instagram.com" className="social-icon" target="_blank" rel="noopener noreferrer">
                    <img src="/img/instagram_logo.svg" alt="Instagram" />
                </a>
                <a href="https://www.youtube.com" className="social-icon" target="_blank" rel="noopener noreferrer">
                    <img src="/img/youtube_logo.svg" alt="YouTube" />
                </a>
            </div>
            <h1 className="header-title">
                <Link to="/">GIO &amp; FABIO'S HAIR SALON</Link>
            </h1>
            <nav className="user-nav">
                {isAuthenticated ? (
                    <>
                        <div className="user-nav-item">
                            {user?.name} {isAdmin() && '(Admin)'}
                        </div>
                        <div className="user-nav-item" onClick={logout} style={{ cursor: 'pointer' }}>
                            Esci
                        </div>
                        <div className="cart-icon" onClick={toggleCart} style={{ cursor: 'pointer', marginLeft: '15px' }}>
                            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                                <circle cx="9" cy="21" r="1"></circle>
                                <circle cx="20" cy="21" r="1"></circle>
                                <path d="M1 1h4l2.68 13.39a2 2 0 0 0 2 1.61h9.72a2 2 0 0 0 2-1.61L23 6H6"></path>
                            </svg>
                            {getTotalItems() > 0 && (
                                <span className="cart-count">{getTotalItems()}</span>
                            )}
                        </div>
                    </>
                ) : (
                    <Link to="/login" className="user-nav-item">Accedi</Link>
                )}
            </nav>
            <nav className="nav-bar">
                <Link to="/services" className="nav-item">Servizi</Link>
                <Link to="/products" className="nav-item">Prodotti</Link>
                <Link to="/contacts" className="nav-item">Contatti</Link>

            </nav>
        </header>
    );
};

export default Header;