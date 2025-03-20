// server/src/main/java/com/hairsalon/service/ServiceService.java
package com.hairsalon.service;

import com.hairsalon.model.Service;
import com.hairsalon.repository.ServiceRepository;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;
import java.util.Optional;

@org.springframework.stereotype.Service
public class ServiceService {

    @Autowired
    private ServiceRepository serviceRepository;
    
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
    
    public Service saveService(Service service) {
        return serviceRepository.save(service);
    }
    
    public void deleteService(Long id) {
        serviceRepository.deleteById(id);
    }
}