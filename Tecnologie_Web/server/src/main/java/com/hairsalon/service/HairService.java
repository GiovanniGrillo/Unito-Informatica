// server/src/main/java/com/hairsalon/service/HairService.java
package com.hairsalon.service;

import com.hairsalon.model.Service;
import com.hairsalon.repository.ServiceRepository;
import jakarta.annotation.PostConstruct;

import java.util.List;
import java.util.Optional;

@org.springframework.stereotype.Service
public class HairService {

    private final ServiceRepository serviceRepository;
    
    public HairService(ServiceRepository serviceRepository) {
        this.serviceRepository = serviceRepository;
    }
    
    @PostConstruct
    public void init() {
        // Inizializzazione dati servizi
        Service service1 = new Service();
        service1.setName("Taglio Donna");
        service1.setDescription("Taglio e piega per donna, personalizzato in base alla forma del viso");
        service1.setPrice(35.0f);
        service1.setDurationMinutes(45);
        service1.setCategory("Taglio");
        service1.setImageUrl("/img/hair_styles/woman_cut.webp");
        serviceRepository.save(service1);
        
        Service service2 = new Service();
        service2.setName("Taglio Uomo");
        service2.setDescription("Taglio classico per uomo, include rifinitura di nuca e basette");
        service2.setPrice(25.0f);
        service2.setDurationMinutes(30);
        service2.setCategory("Taglio");
        service2.setImageUrl("/img/hair_styles/man_cut.webp");
        serviceRepository.save(service2);
        
        Service service3 = new Service();
        service3.setName("Piega e Styling");
        service3.setDescription("Piega professionale con phon e spazzola, per un look perfetto");
        service3.setPrice(25.0f);
        service3.setDurationMinutes(30);
        service3.setCategory("Styling");
        service3.setImageUrl("/img/hair_styles/blow_dry.webp");
        serviceRepository.save(service3);
        
        Service service4 = new Service();
        service4.setName("Permanente");
        service4.setDescription("Trattamento per creare ricci o onde durature sui capelli");
        service4.setPrice(75.0f);
        service4.setDurationMinutes(120);
        service4.setCategory("Trattamento");
        service4.setImageUrl("/img/hair_styles/hair_perm.webp");
        serviceRepository.save(service4);
        
        Service service5 = new Service();
        service5.setName("Colorazione Completa");
        service5.setDescription("Colorazione professionale su tutta la capigliatura, con prodotti di alta qualità");
        service5.setPrice(70.0f);
        service5.setDurationMinutes(120);
        service5.setCategory("Colore");
        service5.setImageUrl("/img/hair_styles/hair_dye.webp");
        serviceRepository.save(service5);
        
        Service service6 = new Service();
        service6.setName("Acconciatura Elegante");
        service6.setDescription("Acconciatura elaborata per eventi speciali, cerimonie o serate importanti");
        service6.setPrice(65.0f);
        service6.setDurationMinutes(60);
        service6.setCategory("Styling");
        service6.setImageUrl("/img/hair_styles/hair_styling.webp");
        serviceRepository.save(service6);
        
        Service service7 = new Service();
        service7.setName("Taglio Uomo Capelli Lunghi");
        service7.setDescription("Taglio e styling per uomo con capelli lunghi o medio-lunghi");
        service7.setPrice(30.0f);
        service7.setDurationMinutes(45);
        service7.setCategory("Taglio");
        service7.setImageUrl("/img/hair_styles/long_hair_man.webp");
        serviceRepository.save(service7);
        
    }
    
    public List<Service> getAllServices() {
        return serviceRepository.findAll();
    }
    
    public Optional<Service> getServiceById(Integer id) {
        return serviceRepository.findById(id);
    }
    
    public List<Service> getServicesByCategory(String category) {
        return serviceRepository.findByCategory(category);
    }
    
    // Il metodo getServicesByExpertiseLevel è stato rimosso come richiesto
    
    // I metodi per la gestione della relazione tra servizi e prodotti sono stati rimossi
    // poiché ora la tabella servizi è indipendente dalla tabella prodotti
    
    public Service saveService(Service service) {
        return serviceRepository.save(service);
    }
    
    public void deleteService(Integer id) {
        serviceRepository.deleteById(id);
    }
}