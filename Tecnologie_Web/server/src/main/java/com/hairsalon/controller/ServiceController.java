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
            @RequestParam(required = false) String category) {
        
        if (category != null) {
            return ResponseEntity.ok(HairService.getServicesByCategory(category));
        }
        return ResponseEntity.ok(HairService.getAllServices());
    }

    @GetMapping("/{id}")
    public ResponseEntity<Service> getService(@PathVariable Integer id) {
        return HairService.getServiceById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping("")
    public ResponseEntity<Service> createService(@RequestBody Service service) {
        return ResponseEntity.ok(HairService.saveService(service));
    }

    // I metodi PUT e DELETE sono stati rimossi come richiesto
}