# Hair Salon Website Project

## Project Overview
This project is a modern, responsive website for a hair salon called "Bellezza Naturale". The website showcases the salon's services, products, and allows customers to book appointments online. The project follows a client-server architecture with a React frontend and a Spring Boot backend for handling appointments, user authentication, and product management.

## Current Development Status

### Frontend (Implemented)
- **Home Page**: Fully implemented with carousel, "Chi Siamo" section, contact information, and image gallery
- **Services Page**: Implemented with service categories, descriptions, and pricing
- **Products Page**: Implemented with product listings, categories, and cart functionality
- **Authentication**: Login functionality with user roles (client/admin)
- **Cart Context**: Shopping cart functionality implemented with React Context API

### Backend (Implemented)
- Spring Boot project structure set up
- Database configuration with JPA
- REST API endpoints for authentication, products, and services
- Repository and service layers implemented
- Data models defined with JPA annotations
- Default data initialization for testing

## Technologies Used

### Frontend
- **React 19**: Modern UI library for building component-based interfaces
- **TypeScript**: For type-safe JavaScript development
- **Vite 6**: Fast build tool and development server
- **React Router 7**: For client-side routing
- **React Bootstrap 2**: UI component library based on Bootstrap 5
- **CSS**: Custom styling with modular CSS files
- **Context API**: For state management (auth, cart)

### Backend
- **Spring Boot 3.4**: Java-based framework for building web applications
- **Spring Data JPA**: For database access and ORM
- **Spring Security**: For authentication and authorization
- **MySQL**: Relational database for storing application data
- **Lombok**: For reducing boilerplate code
- **Maven**: For dependency management and build automation

## Key Features

### Home Page
- Carousel for showcasing salon highlights
- "Chi Siamo" (About Us) section introducing the salon
- Contact information
- Image gallery

### Services Page
- Comprehensive list of salon services with descriptions
- Service categories including:
  - Men's haircuts
  - Women's haircuts
  - Styling and blow-drying
  - Perms
  - Hair coloring
- Service cards with images, descriptions, and pricing
- Booking functionality (partially implemented)
  - Service selection interface
  - Appointment form UI
  - Backend integration pending

### Products Page
- Professional hair care products available for purchase
- Product categories including:
  - Shampoos and conditioners
  - Hair treatments and masks
  - Styling products
  - Heat protection products
- Product cards with images, descriptions, and pricing
- Shopping cart functionality
  - Add to cart functionality
  - Quantity selection
  - Cart display

### Authentication System
- User login functionality
- Role-based access (client/admin)
- Protected routes
- Context-based state management

## API Flow Examples

### Authentication Flow

1. **Frontend Request (Login):**
```typescript
// From AuthContext.tsx
const login = async (email: string, password: string): Promise<boolean> => {
  try {
    const response = await fetch('http://localhost:8080/api/auth/login', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ email, password }),
    });

    if (response.ok) {
      const userData = await response.json();
      setUser(userData);
      localStorage.setItem('user', JSON.stringify(userData));
      return true;
    }
    return false;
  } catch (error) {
    console.error('Errore durante il login:', error);
    return false;
  }
};
```

2. **Backend Controller (AuthController.java):**
```java
@PostMapping("/login")
public ResponseEntity<?> login(@RequestBody Map<String, String> credentials) {
    String email = credentials.get("email");
    String password = credentials.get("password");

    if (email == null || password == null) {
        Map<String, String> error = new HashMap<>();
        error.put("message", "Email e password sono richiesti");
        return ResponseEntity.badRequest().body(error);
    }

    Optional<User> userOpt = userService.authenticate(email, password);

    if (userOpt.isPresent()) {
        User user = userOpt.get();
        // Non inviare la password al frontend
        Map<String, Object> response = new HashMap<>();
        response.put("id", user.getId());
        response.put("name", user.getName());
        response.put("email", user.getEmail());
        response.put("role", user.getRole().toLowerCase());

        return ResponseEntity.ok(response);
    } else {
        Map<String, String> error = new HashMap<>();
        error.put("message", "Credenziali non valide");
        return ResponseEntity.status(401).body(error);
    }
}
```

3. **Service Layer (UserService.java):**
```java
public Optional<User> authenticate(String email, String password) {
    Optional<User> userOpt = userRepository.findByEmail(email);

    if (userOpt.isPresent()) {
        User user = userOpt.get();
        // In produzione, confrontare password criptate
        if (user.getPassword().equals(password)) {
            // Autenticazione riuscita
            return Optional.of(user);
        }
    }
    return Optional.empty();
}
```

4. **Repository Layer (UserRepository.java):**
```java
@Repository
public interface UserRepository extends JpaRepository<User, Integer> {
    Optional<User> findByEmail(String email);
}
```

### Products Flow

1. **Frontend Request (Fetch Products):**
```typescript
// From ProductsPage.tsx
const fetchProducts = async () => {
  try {
    const response = await fetch('http://localhost:8080/products');
    if (!response.ok) {
      throw new Error('Errore nel caricamento dei prodotti');
    }
    const data = await response.json();
    setProducts(data);
    setFilteredProducts(data);

    // Estrai le categorie uniche dai prodotti
    const uniqueCategories = [...new Set(data.map((product: Product) => product.category))].sort();
    setCategories(uniqueCategories as string[]);
    
    setError(null);
  } catch (error) {
    setError('Si è verificato un errore durante il caricamento dei prodotti.');
    setProducts([]);
    setFilteredProducts([]);
    console.error('Errore:', error);
  } finally {
    setLoading(false);
  }
};
```

2. **Backend Controller (ProductController.java):**
```java
@GetMapping("")
public ResponseEntity<List<Product>> products(@RequestParam(required = false) String category) {
    if (category != null) {
        return ResponseEntity.ok(productService.getProductsByCategory(category));
    }
    return ResponseEntity.ok(productService.getAllProducts());
}
```

3. **Service Layer (ProductService.java):**
```java
public List<Product> getAllProducts() {
    return productRepository.findAll();
}

public List<Product> getProductsByCategory(String category) {
    return productRepository.findByCategory(category);
}
```

4. **Repository Layer (ProductRepository.java):**
```java
@Repository
public interface ProductRepository extends JpaRepository<Product, Integer> {
    List<Product> findByCategory(String category);
}
```

### Services Flow

1. **Frontend Request (Fetch Services):**
```typescript
// From ServicesPage.tsx
const fetchServices = async () => {
  try {
    setLoading(true);
    const response = await fetch('http://localhost:8080/services');
    
    if (!response.ok) {
      throw new Error('Errore nel caricamento dei servizi');
    }
    
    const data = await response.json();
    
    // Mappiamo i dati del backend al formato richiesto dal frontend
    const mappedServices = data.map((service: any) => ({
      id: service.id,
      category: service.category,
      title: service.name,
      price: parseFloat(service.price),
      description: service.description,
      imageSrc: service.imageUrl || '/img/hair_styles/default.webp',
    }));
    
    setServices(mappedServices);
    setFilteredServices(mappedServices);
    
    // Estrai le categorie uniche dai servizi
    const uniqueCategories = [...new Set(mappedServices.map((service: Service) => service.category))].sort();
    setCategories(uniqueCategories as string[]);
    
    setError(null);
  } catch (err) {
    console.error('Errore nel caricamento dei servizi:', err);
    setError('Impossibile caricare i servizi. Riprova più tardi.');
    setServices([]);
    setFilteredServices([]);
  } finally {
    setLoading(false);
  }
};
```

2. **Backend Controller (ServiceController.java):**
```java
@GetMapping("")
public ResponseEntity<List<Service>> services(
        @RequestParam(required = false) String category) {
    
    if (category != null) {
        return ResponseEntity.ok(HairService.getServicesByCategory(category));
    }
    return ResponseEntity.ok(HairService.getAllServices());
}
```

3. **Service Layer (HairService.java):**
```java
public List<Service> getAllServices() {
    return serviceRepository.findAll();
}

public List<Service> getServicesByCategory(String category) {
    return serviceRepository.findByCategory(category);
}
```

4. **Repository Layer (ServiceRepository.java):**
```java
@Repository
public interface ServiceRepository extends JpaRepository<Service, Integer> {
    List<Service> findByCategory(String category);
}
```

## Setup and Installation

### Prerequisites
- Node.js (latest LTS version recommended)
- npm or yarn package manager
- Java Development Kit (JDK) 17 or higher
- Maven 3.6 or higher
- MySQL 8.0 or higher

### Frontend Setup
1. Navigate to the client directory:
   ```
   cd Tecnologie_Web/client
   ```

2. Install dependencies:
   ```
   npm install
   ```

3. Start the development server:
   ```
   npm run dev
   ```

4. Build for production:
   ```
   npm run build
   ```

### Backend Setup
1. Navigate to the server directory:
   ```
   cd Tecnologie_Web/server
   ```

2. Configure the database connection in `src/main/resources/application.properties` (create this file if it doesn't exist):
   ```properties
   spring.datasource.url=jdbc:mysql://localhost:3306/hairsalon
   spring.datasource.username=your_username
   spring.datasource.password=your_password
   spring.jpa.hibernate.ddl-auto=update
   spring.jpa.properties.hibernate.dialect=org.hibernate.dialect.MySQLDialect
   ```

3. Build the application:
   ```
   mvn clean install
   ```

4. Run the application:
   ```
   mvn spring-boot:run
   ```

## Development Roadmap

### Frontend Tasks (In Progress)
- Implement "Book Now" section with full functionality
- Improve Services section layout:
  - Reduce size of haircut boxes
  - Align and column layout (reference: https://voguevertu.it/servizi/)
  - Add image carousel for each haircut type
- Enhance Products section:
  - Add "View All" section for each product category
  - Add "View All" section for each haircut type
  - Expand product catalog with additional items
- Connect frontend to backend API endpoints
- Implement form validation
- Add responsive design improvements for mobile devices

### Backend Tasks (In Progress)
- Complete database schema for users, permissions, appointment calendar, and shopping cart
- Implement JWT-based authentication system
- Create API endpoints for:
  - User registration and profile management
  - Appointment booking and management
  - Product catalog and inventory management
  - Shopping cart and order processing
- Implement data validation and error handling
- Set up logging and monitoring
- Configure CORS and security settings

## Project Timeline
- **Phase 1 (Completed)**: Frontend UI implementation
- **Phase 2 (In Progress)**: Backend API development and database setup
- **Phase 3 (Planned)**: Integration of frontend and backend
- **Phase 4 (Planned)**: Testing, optimization, and deployment

## Contributing
This project is part of the Web Technologies course at the University of Turin. Please follow the established code style and commit guidelines when contributing.

### Coding Standards
- Use consistent indentation (2 spaces)
- Follow component naming conventions (PascalCase for components)
- Write meaningful commit messages
- Document code where necessary
- Write unit tests for critical functionality