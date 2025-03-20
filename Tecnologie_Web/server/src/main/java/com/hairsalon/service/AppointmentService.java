// server/src/main/java/com/hairsalon/service/AppointmentService.java
package com.hairsalon.service;

import com.hairsalon.model.Appointment;
import com.hairsalon.model.Appointment.AppointmentStatus;
import com.hairsalon.model.Client;
import com.hairsalon.model.Product;
import com.hairsalon.model.Service;
// Stylist import removed
import com.hairsalon.repository.AppointmentRepository;
import org.springframework.beans.factory.annotation.Autowired;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@org.springframework.stereotype.Service
public class AppointmentService {

    @Autowired
    private AppointmentRepository appointmentRepository;
    
    // StylistService reference removed
    
    @Autowired
    private ProductService productService;
    
    public List<Appointment> getAllAppointments() {
        return appointmentRepository.findAll();
    }
    
    public Optional<Appointment> getAppointmentById(Long id) {
        return appointmentRepository.findById(id);
    }
    
    public List<Appointment> getAppointmentsByClient(Client client) {
        return appointmentRepository.findByClient(client);
    }
    
    // Stylist-related method removed
    
    public List<Appointment> getAppointmentsByStatus(AppointmentStatus status) {
        return appointmentRepository.findByStatus(status);
    }
    
    public List<Appointment> getAppointmentsByDateRange(LocalDateTime start, LocalDateTime end) {
        return appointmentRepository.findByAppointmentTimeBetween(start, end);
    }
    
    public List<Appointment> getUpcomingAppointmentsByClient(Client client, LocalDateTime now) {
        return appointmentRepository.findByClientAndAppointmentTimeAfter(client, now);
    }
    
    // Stylist-related method removed
    
    // Stylist availability method removed
    
    public Appointment bookAppointment(Appointment appointment) {
        // Calculate end time based on services duration
        int totalDurationMinutes = appointment.getSelectedServices().stream()
                .mapToInt(Service::getDurationMinutes)
                .sum();
        
        LocalDateTime endTime = appointment.getAppointmentTime().plusMinutes(totalDurationMinutes);
        appointment.setEndTime(endTime);
        
        // Stylist-related checks removed
        
        // Check product inventory for required products
        checkProductInventory(appointment.getSelectedServices());
        
        // Set initial status
        appointment.setStatus(AppointmentStatus.BOOKED);
        
        return appointmentRepository.save(appointment);
    }
    
    public Appointment updateAppointmentStatus(Long id, AppointmentStatus newStatus) {
        return appointmentRepository.findById(id)
                .map(appointment -> {
                    appointment.setStatus(newStatus);
                    return appointmentRepository.save(appointment);
                })
                .orElseThrow(() -> new RuntimeException("Appointment not found"));
    }
    
    public Appointment rescheduleAppointment(Long id, LocalDateTime newTime) {
        return appointmentRepository.findById(id)
                .map(appointment -> {
                    // Calculate new end time
                    int totalDurationMinutes = appointment.getSelectedServices().stream()
                            .mapToInt(Service::getDurationMinutes)
                            .sum();
                    
                    LocalDateTime newEndTime = newTime.plusMinutes(totalDurationMinutes);
                    
                    // Stylist availability check removed
                    
                    appointment.setAppointmentTime(newTime);
                    appointment.setEndTime(newEndTime);
                    return appointmentRepository.save(appointment);
                })
                .orElseThrow(() -> new RuntimeException("Appointment not found"));
    }
    
    public void cancelAppointment(Long id) {
        appointmentRepository.findById(id)
                .map(appointment -> {
                    appointment.setStatus(AppointmentStatus.CANCELLED);
                    return appointmentRepository.save(appointment);
                })
                .orElseThrow(() -> new RuntimeException("Appointment not found"));
    }
    
    public void deleteAppointment(Long id) {
        appointmentRepository.deleteById(id);
    }
    
    // Stylist expertise verification method removed
    
    /**
     * Checks if there is sufficient inventory for all products required by the services
     * @param services The services to check product inventory for
     * @throws RuntimeException if there is insufficient inventory
     */
    private void checkProductInventory(List<Service> services) {
        // Create a map to track total required quantity for each product
        Map<Long, Integer> requiredProductQuantities = new HashMap<>();
        
        // Calculate total required quantity for each product
        for (Service service : services) {
            for (Product product : service.getRequiredProducts()) {
                Long productId = product.getId();
                requiredProductQuantities.put(productId, 
                        requiredProductQuantities.getOrDefault(productId, 0) + 1);
            }
        }
        
        // Check if there is sufficient inventory for each product
        for (Map.Entry<Long, Integer> entry : requiredProductQuantities.entrySet()) {
            Long productId = entry.getKey();
            Integer requiredQuantity = entry.getValue();
            
            Product product = productService.getProductById(productId)
                    .orElseThrow(() -> new RuntimeException("Product not found: " + productId));
            
            if (product.getAvailableQuantity() < requiredQuantity) {
                throw new RuntimeException("Insufficient inventory for product: " + 
                        product.getName() + ". Required: " + requiredQuantity + 
                        ", Available: " + product.getAvailableQuantity());
            }
        }
    }
}