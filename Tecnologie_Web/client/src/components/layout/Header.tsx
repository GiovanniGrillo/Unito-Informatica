// src/components/layout/Header.tsx
import React, { useState } from 'react';
import {Link} from "react-router-dom";

const Header: React.FC = () => {
  // State to track if mobile menu is open
  const [isMenuOpen, setIsMenuOpen] = useState(false);

  // Funzione per lo scroll smooth alle sezioni
  const scrollToSection = (sectionId: string): void => {
    const element = document.getElementById(sectionId);
    if (element) {
      element.scrollIntoView({ behavior: 'smooth' });
    }
    // Close menu after clicking a nav item on mobile
    setIsMenuOpen(false);
  };

  // Toggle mobile menu
  const toggleMenu = (): void => {
    setIsMenuOpen(!isMenuOpen);
  };

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
        <div className="user-nav-item">User</div>
        <div className="user-nav-item">Esci</div>
      </nav>
      
      {/* Hamburger menu button */}
      <div 
        className={`hamburger-menu ${isMenuOpen ? 'active' : ''}`} 
        onClick={toggleMenu}
      >
        <span></span>
        <span></span>
        <span></span>
      </div>
      
      {/* Navigation overlay for mobile */}
      <div 
        className={`nav-overlay ${isMenuOpen ? 'active' : ''}`}
        onClick={() => setIsMenuOpen(false)}
      ></div>
      
      <nav className={`nav-bar ${isMenuOpen ? 'active' : ''}`}>
        <button onClick={() => scrollToSection('chi-siamo')} className="nav-item">Chi siamo</button>
        <Link to="/services" className="nav-item" onClick={() => setIsMenuOpen(false)}>Servizi</Link>
        <Link to="/products" className="nav-item" onClick={() => setIsMenuOpen(false)}>Prodotti</Link>
        <button onClick={() => scrollToSection('contatti')} className="nav-item">Contatti</button>
      </nav>
    </header>
  );
};

export default Header;