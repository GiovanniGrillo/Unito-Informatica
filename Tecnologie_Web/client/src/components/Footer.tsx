import React from 'react';

const Footer: React.FC = () => {
  return (
    <footer className="footer">
      <p className="project-info">
        <span className="highlight">Elegance Hair Salon</span> è un salone di bellezza situato a Milano, Italia.<br />
        Dedicato alla cura dei capelli con prodotti di alta qualità e servizi personalizzati.
      </p>

      <div className="copyright">
        <img alt="Creative Commons License" className="cclicense" src="/img/hair-salon_cc.png" loading="lazy" />
        <p className="copyright-text">&copy; 2024-2025 Grillo Giovanni, Carturan Fabio.</p>
      </div>
    </footer>
  );
};

export default Footer;