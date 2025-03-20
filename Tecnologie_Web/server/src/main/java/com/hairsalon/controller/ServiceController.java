// server/src/main/java/com/hairsalon/controller/ServiceController.java
package com.hairsalon.controller;

import com.hairsalon.model.Service;
import com.hairsalon.service.ServiceService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/services")
@CrossOrigin(origins = "http://localhost:5173")
public class ServiceController {

    @Autowired
    private ServiceService serviceService;

    @GetMapping
    public List<Service> getAllServices() {
        return serviceService.getAllServices();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Service> getServiceById(@PathVariable Long id) {
        return serviceService.getServiceById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @GetMapping("/category/{category}")
    public List<Service> getServicesByCategory(@PathVariable String category) {
        return serviceService.getServicesByCategory(category);
    }

    @GetMapping("/expertise/{expertiseLevel}")
    public List<Service> getServicesByExpertiseLevel(@PathVariable String expertiseLevel) {
        return serviceService.getServicesByExpertiseLevel(expertiseLevel);
    }

    @GetMapping("/max-duration/{maxDuration}")
    public List<Service> getServicesByMaxDuration(@PathVariable Integer maxDuration) {
        return serviceService.getServicesByMaxDuration(maxDuration);
    }

    @PostMapping
    public Service createService(@RequestBody Service service) {
        return serviceService.saveService(service);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Service> updateService(@PathVariable Long id, @RequestBody Service service) {
        return serviceService.getServiceById(id)
                .map(existingService -> {
                    service.setId(id);
                    return ResponseEntity.ok(serviceService.saveService(service));
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteService(@PathVariable Long id) {
        return serviceService.getServiceById(id)
                .map(service -> {
                    serviceService.deleteService(id);
                    return ResponseEntity.ok().<Void>build();
                })
                .orElse(ResponseEntity.notFound().build());
    }
}