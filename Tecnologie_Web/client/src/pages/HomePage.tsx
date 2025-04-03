// src/pages/HomePage.tsx
import React from 'react';
import Carousel from '../components/features/Carousel';
import Gallery from '../components/features/Gallery';

const HomePage: React.FC = () => {
  return (
    <main>
      <Carousel />
      
      <section className="content-area">
        {/* Sezione Chi Siamo */}
        <div className="section" id="chi-siamo">
          <h2>Chi Siamo</h2>
          <p>
            Benvenuti da <strong>Bellezza Naturale</strong>, il salone di bellezza dove l'arte dei capelli incontra la passione per il benessere.
            Da oltre 10 anni, il nostro team di professionisti altamente qualificati si dedica a creare look unici e su misura per ogni cliente.
            Crediamo che ogni persona sia unica, ed è per questo che ci impegniamo a offrire un'esperienza personalizzata, utilizzando solo
            prodotti di alta qualità e rispettosi dell'ambiente.
          </p>
        </div>

        {/* Sezione Contatti */}
        <div className="section" id="contatti">
          <h2>Contatti</h2>
          <ul>
            <li><strong>Indirizzo</strong>: Via pessinetto, 12, 10149 Torino (TO), Italia</li>
            <li><strong>Telefono</strong>: +39 011 234567</li>
            <li><strong>Email</strong>: info@bellezzanaturale.it</li>
          </ul>
        </div>

        {/* Sezione Orari */}
        <div className="section" id="orari">
          <h2>Orari di Apertura</h2>
          <ul>
            <li><strong>Lunedì - Venerdì</strong>: 9:00 - 19:00</li>
            <li><strong>Sabato</strong>: 9:00 - 17:00</li>
            <li><strong>Domenica</strong>: Chiuso</li>
          </ul>
        </div>
      </section>
      
      <Gallery />
    </main>
  );
};

export default HomePage;