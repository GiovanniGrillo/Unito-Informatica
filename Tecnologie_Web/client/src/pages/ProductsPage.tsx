// src/pages/ProductsPage.tsx
import React, { useState } from 'react';
import ProductCard from '../components/features/ProductCard';
import { Product } from '../types/Product';

const ProductsPage: React.FC = () => {
  // Stato per tenere traccia del prodotto selezionato
  const [selectedProduct, setSelectedProduct] = useState<number | null>(null);
  
  // Dati di esempio (verrebbero recuperati da un'API in un'app reale)
  const products: Product[] = [
    {
      id: 1,
      category: "SHAMPOO PROFESSIONALE",
      title: "Shampoo Idratante",
      price: 18,
      description: "Shampoo professionale idratante per capelli secchi e danneggiati. Arricchito con oli naturali e vitamine per nutrire in profondità.",
      imageSrc: "/img/products/shampoo_idratante.webp",
    },
    {
      id: 2,
      category: "BALSAMO PROFESSIONALE",
      title: "Balsamo Riparatore",
      price: 20,
      description: "Balsamo intensivo che ripara e protegge i capelli danneggiati. Formula arricchita con cheratina e proteine della seta per capelli morbidi e luminosi.",
      imageSrc: "/img/products/balsamo_riparatore.webp",
    },
    {
      id: 3,
      category: "TRATTAMENTI INTENSIVI",
      title: "Maschera Nutriente",
      price: 25,
      description: "Maschera nutriente profonda per capelli secchi e sfibrati. Trattamento settimanale per ripristinare l'idratazione e la vitalità dei capelli.",
      imageSrc: "/img/products/maschera_nutriente.webp",
    },
    {
      id: 4,
      category: "STYLING PROFESSIONALE",
      title: "Gel Modellante",
      price: 15,
      description: "Gel modellante a tenuta forte per creare acconciature definite e di lunga durata. Non lascia residui e si elimina facilmente con lo shampoo.",
      imageSrc: "/img/products/gel_modellante.webp",
    },
    {
      id: 5,
      category: "PROTEZIONE TERMICA",
      title: "Spray Protettivo",
      price: 22,
      description: "Spray protettivo contro il calore di phon e piastre. Previene i danni causati dagli strumenti termici e mantiene i capelli sani e lucenti.",
      imageSrc: "/img/products/spray_protettivo.webp",
    }
  ];

  // Gestione dell'acquisto
  const handleBuyProduct = (productId: number) => {
    setSelectedProduct(productId);
    // In un'app reale, qui potresti aprire un modale di conferma o navigare a un carrello
    alert(`Prodotto selezionato: ${products.find(p => p.id === productId)?.title}`);
  };

  return (
    <main>
      <section className="services-content-area">
        <div className="section" id="prodotti">
          <h2>Prodotti</h2>
          <p>
            Scopri la nostra linea di prodotti professionali per la cura dei capelli. Utilizziamo solo ingredienti di alta qualità per garantire risultati eccezionali.
          </p>
          <ul>
            <li>Shampoo e balsami professionali</li>
            <li>Trattamenti intensivi e maschere</li>
            <li>Prodotti per lo styling</li>
            <li>Protezione termica e UV</li>
          </ul>
        </div>
      </section>
      
      {/* Se c'è un prodotto selezionato, mostra un box informativo */}
      {selectedProduct && (
        <div className="selected-service-info">
          <p>Hai selezionato: {products.find(p => p.id === selectedProduct)?.title}</p>
          <button onClick={() => setSelectedProduct(null)}>Annulla selezione</button>
        </div>
      )}
      
      {products.map(product => (
        <ProductCard 
          key={product.id}
          product={product}
          onBuy={handleBuyProduct}
        />
      ))}
    </main>
  );
};

export default ProductsPage;