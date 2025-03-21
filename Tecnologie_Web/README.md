# Hair Salon Website Project

## Project Overview
This project is a modern, responsive website for a hair salon called "Bellezza Naturale". The website showcases the salon's services, products, and allows customers to book appointments online. The project follows a client-server architecture with a React frontend and a Spring Boot backend for handling appointments, user authentication, and product management.

## Current Development Status

### Frontend (Implemented)
- **Home Page**: Fully implemented with carousel, "Chi Siamo" section, contact information, and image gallery
- **Services Page**: Implemented with service categories, descriptions, and pricing
- **Products Page**: Basic implementation with product listings and categories
- **Authentication**: Basic login functionality with user roles (client/admin)

### Backend (In Progress)
- Spring Boot project structure set up
- Database configuration with JPA
- Security configuration initialized
- API endpoints planned but not fully implemented


## Technologies Used

### Frontend
- **React 19**: Modern UI library for building component-based interfaces
- **TypeScript**: For type-safe JavaScript development
- **Vite 6**: Fast build tool and development server
- **React Router 7**: For client-side routing
- **React Bootstrap 2**: UI component library based on Bootstrap 5
- **CSS**: Custom styling with modular CSS files

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
- Shopping cart functionality (UI implemented, backend pending)
  - Add to cart functionality
  - Quantity selection
  - Cart display

### Authentication System
- User login functionality
- Role-based access (client/admin)
- Protected routes
- Context-based state management

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