// server/src/main/java/com/hairsalon/service/HairService.java
package com.hairsalon.service;

import com.hairsalon.model.Service;
import com.hairsalon.repository.ServiceRepository;
import jakarta.annotation.PostConstruct;

import java.math.BigDecimal;
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
        service1.setDescription("Taglio e piega per donna");
        service1.setPrice(new BigDecimal("35.00"));
        service1.setDurationMinutes(45);
        service1.setRequiredExpertiseLevel("Intermedio");
        service1.setCategory("Taglio");
        service1.setImageUrl("/images/services/taglio-donna.jpg");
        Service savedService1 = serviceRepository.save(service1);
        
        Service service2 = new Service();
        service2.setName("Taglio Uomo");
        service2.setDescription("Taglio classico per uomo");
        service2.setPrice(new BigDecimal("25.00"));
        service2.setDurationMinutes(30);
        service2.setRequiredExpertiseLevel("Base");
        service2.setCategory("Taglio");
        service2.setImageUrl("/images/services/taglio-uomo.jpg");
        Service savedService2 = serviceRepository.save(service2);
        
        Service service3 = new Service();
        service3.setName("Colorazione Completa");
        service3.setDescription("Colorazione professionale su tutta la capigliatura");
        service3.setPrice(new BigDecimal("70.00"));
        service3.setDurationMinutes(120);
        service3.setRequiredExpertiseLevel("Avanzato");
        service3.setCategory("Colore");
        service3.setImageUrl("/images/services/colorazione.jpg");
        Service savedService3 = serviceRepository.save(service3);
        
        Service service4 = new Service();
        service4.setName("Mèches");
        service4.setDescription("Mèches con tecnica a cartine");
        service4.setPrice(new BigDecimal("85.00"));
        service4.setDurationMinutes(150);
        service4.setRequiredExpertiseLevel("Avanzato");
        service4.setCategory("Colore");
        service4.setImageUrl("/images/services/meches.jpg");
        Service savedService4 = serviceRepository.save(service4);
        
        Service service5 = new Service();
        service5.setName("Trattamento Anticaduta");
        service5.setDescription("Trattamento professionale per contrastare la caduta dei capelli");
        service5.setPrice(new BigDecimal("55.00"));
        service5.setDurationMinutes(60);
        service5.setRequiredExpertiseLevel("Specializzato");
        service5.setCategory("Trattamento");
        service5.setImageUrl("/images/services/anticaduta.jpg");
        Service savedService5 = serviceRepository.save(service5);
        
        // I servizi sono ora indipendenti dai prodotti, come richiesto
    }
    
    public List<Service> getAllServices() {
        return serviceRepository.findAll();
    }
    
    public Optional<Service> getServiceById(Long id) {
        return serviceRepository.findById(id);
    }
    
    public List<Service> getServicesByCategory(String category) {
        return serviceRepository.findByCategory(category);
    }
    
    public List<Service> getServicesByExpertiseLevel(String expertiseLevel) {
        return serviceRepository.findByRequiredExpertiseLevel(expertiseLevel);
    }
    
    public List<Service> getServicesByMaxDuration(Integer maxDuration) {
        return serviceRepository.findByDurationMinutesLessThanEqual(maxDuration);
    }
    
    // I metodi per la gestione della relazione tra servizi e prodotti sono stati rimossi
    // poiché ora la tabella servizi è indipendente dalla tabella prodotti
    
    public Service saveService(Service service) {
        return serviceRepository.save(service);
    }
    
    public void deleteService(Long id) {
        serviceRepository.deleteById(id);
    }
}