import React from 'react';
import ServiceBox from './ServiceBox';

interface ServiceData {
  category: string;
  title: string;
  description: string;
  imageSrc: string;
  imageAlt: string;
}

const Services: React.FC = () => {
  const services: ServiceData[] = [
    {
      category: 'TAGLI E PIEGHE PER UOMO A MILANO',
      title: 'Taglio Uomo €30',
      description: 'Affidati a degli esperti del taglio per dare nuova vita alla tua chioma: sapranno ascoltarti e capire il tuo stile per tagliare e rasare esattamente come vuoi tu.',
      imageSrc: '/img/hair_styles/man_cut.webp',
      imageAlt: 'Taglio Uomo'
    },
    {
      category: 'TAGLI E PIEGHE PER DONNA A MILANO',
      title: 'Taglio Donna €40',
      description: 'Affidati ai nostri hairstylist per un look personalizzato e alla moda. Dalla piega al taglio su misura, ci prendiamo cura dei tuoi capelli con prodotti di alta qualità.',
      imageSrc: '/img/hair_styles/woman_cut.webp',
      imageAlt: 'Taglio Donna'
    },
    {
      category: 'STYLING E PIEGA A MILANO',
      title: 'Piega €25',
      description: 'Valorizza il tuo look con una piega professionale su misura per te. Che tu voglia capelli lisci, mossi o voluminosi, i nostri esperti sapranno esaltare la tua bellezza naturale.',
      imageSrc: '/img/hair_styles/blow_dry.webp',
      imageAlt: 'Piega'
    },
    {
      category: 'PERMANENTE PROFESSIONALE A MILANO',
      title: 'Permanente €60',
      description: 'Dona ai tuoi capelli volume e onde perfette con la nostra permanente su misura. I nostri specialisti utilizzeranno tecniche avanzate per garantirti un risultato naturale e duraturo.',
      imageSrc: '/img/hair_styles/hair_perm.webp',
      imageAlt: 'Permanente'
    },
    {
      category: 'COLORAZIONE PROFESSIONALE A MILANO',
      title: 'Tinta €100',
      description: 'Rinnova il tuo look con una colorazione personalizzata. Dai colori naturali ai toni più audaci, i nostri esperti ti aiuteranno a scegliere la nuance perfetta per il tuo stile.',
      imageSrc: '/img/hair_styles/hair_dye.webp',
      imageAlt: 'Tinta'
    }
  ];

  return (
    <main>
      <section className="services-content-area">
        <div className="section" id="servizi">
          <h2>Servizi</h2>
          <p>
            Offriamo una gamma di servizi per la cura e lo styling dei capelli, con prodotti di alta qualità e tecniche avanzate.
          </p>
          <ul>
            <li>Taglio e styling personalizzato</li>
            <li>Colore e trattamenti per capelli</li>
            <li>Trattamenti ristrutturanti</li>
            <li>Acconciature per eventi</li>
          </ul>
        </div>
      </section>
      
      {services.map((service, index) => (
        <ServiceBox 
          key={index}
          category={service.category}
          title={service.title}
          description={service.description}
          imageSrc={service.imageSrc}
          imageAlt={service.imageAlt}
        />
      ))}
    </main>
  );
};

export default Services;