import React from 'react';
import { Link } from 'react-router-dom';

const Header: React.FC = () => {
  // Function to handle smooth scrolling to sections
  const scrollToSection = (sectionId: string): void => {
    const element = document.getElementById(sectionId);
    if (element) {
      element.scrollIntoView({ behavior: 'smooth' });
    }
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
        <Link to="/">GIO & FABIO'S HAIR SALON</Link>
      </h1>
      <nav className="user-nav">
        <div className="user-nav-item">User</div>
        <div className="user-nav-item">Esci</div>
      </nav>
      <nav className="nav-bar">
        <button onClick={() => scrollToSection('chi-siamo')} className="nav-item">Chi siamo</button>
        <Link to="/services" className="nav-item">Servizi</Link>
        <button onClick={() => scrollToSection('contatti')} className="nav-item">Contatti</button>
      </nav>
    </header>
  );
};

export default Header;