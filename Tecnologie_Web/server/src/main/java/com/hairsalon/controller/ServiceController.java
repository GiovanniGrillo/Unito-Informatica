// server/src/main/java/com/hairsalon/controller/ServiceController.java
package com.hairsalon.controller;

import com.hairsalon.model.Service;
import com.hairsalon.service.HairService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/services")
@CrossOrigin(origins = "http://localhost:5173")
public class ServiceController {

    private final HairService HairService;
    
    public ServiceController(HairService HairService) {
        this.HairService = HairService;
    }

    @GetMapping("")
    public ResponseEntity<List<Service>> services(
            @RequestParam(required = false) String category,
            @RequestParam(required = false) String expertiseLevel,
            @RequestParam(required = false) Integer maxDuration) {
        
        if (category != null) {
            return ResponseEntity.ok(HairService.getServicesByCategory(category));
        }
        if (expertiseLevel != null) {
            return ResponseEntity.ok(HairService.getServicesByExpertiseLevel(expertiseLevel));
        }
        if (maxDuration != null) {
            return ResponseEntity.ok(HairService.getServicesByMaxDuration(maxDuration));
        }
        
        return ResponseEntity.ok(HairService.getAllServices());
    }

    @GetMapping("/{id}")
    public ResponseEntity<Service> getService(@PathVariable Long id) {
        return HairService.getServiceById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping("")
    public ResponseEntity<Service> createService(@RequestBody Service service) {
        return ResponseEntity.ok(HairService.saveService(service));
    }

    @PutMapping("/{id}")
    public ResponseEntity<Service> updateService(@PathVariable Long id, @RequestBody Service service) {
        return HairService.getServiceById(id)
                .map(existingService -> {
                    service.setId(id);
                    return ResponseEntity.ok(HairService.saveService(service));
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteService(@PathVariable Long id) {
        return HairService.getServiceById(id)
                .map(service -> {
                    HairService.deleteService(id);
                    return ResponseEntity.ok().<Void>build();
                })
                .orElse(ResponseEntity.notFound().build());
    }
}