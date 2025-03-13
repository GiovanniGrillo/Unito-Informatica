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
            <li><strong>Indirizzo</strong>: Via della Bellezza, 123 - 20121 Milano (Italia)</li>
            <li><strong>Telefono</strong>: +39 06 1234 5678</li>
            <li><strong>Email</strong>: info@bellezzanaturale.it</li>
          </ul>
        </div>
      </section>
      
      <Gallery />
    </main>
  );
};

export default HomePage;