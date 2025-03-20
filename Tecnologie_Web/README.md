# Hair Salon Website Project

## Project Overview
This project is a modern, responsive website for a hair salon called "Bellezza Naturale". The website showcases the salon's services, products, and allows customers to book appointments online. The project follows a client-server architecture with a React frontend and a planned backend for handling appointments and user data.

## Folder Structure

```
Tecnologie_Web/
├── client/               # Frontend application
│   ├── public/           # Static assets and HTML templates
│   │   └── img/          # Images used throughout the site
│   ├── src/              # Source code
│   │   ├── assets/       # Frontend assets (icons, etc.)
│   │   ├── components/   # Reusable React components
│   │   │   ├── auth/     # Authentication components
│   │   │   ├── common/   # Shared UI components
│   │   │   ├── features/ # Feature-specific components
│   │   │   └── layout/   # Layout components (Header, Footer)
│   │   ├── pages/        # Page components
│   │   ├── services/     # API services and utilities
│   │   ├── styles/       # CSS stylesheets
│   │   └── types/        # TypeScript type definitions
│   └── package.json      # Frontend dependencies
├── server/               # Backend application (planned)
└── TODO                  # Project tasks and requirements
```

## Technologies Used

### Frontend
- **React 19**: Modern UI library for building component-based interfaces
- **TypeScript**: For type-safe JavaScript development
- **Vite**: Fast build tool and development server
- **React Router**: For client-side routing
- **React Bootstrap**: UI component library based on Bootstrap
- **CSS**: Custom styling with modular CSS files

### Backend (Planned)
- Database system for storing user information, appointments, and product inventory
- Authentication system for user accounts
- API endpoints for appointment booking and product management

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
- Booking functionality (planned)

### Products Page
- Professional hair care products available for purchase
- Product categories including:
  - Shampoos and conditioners
  - Hair treatments and masks
  - Styling products
  - Heat protection products
- Product cards with images, descriptions, and pricing
- Shopping cart functionality (planned)

### Booking System (Planned)
- Online appointment scheduling
- Calendar integration
- Service selection
- Stylist selection

## Setup and Installation

### Prerequisites
- Node.js (latest LTS version recommended)
- npm or yarn package manager

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

## Development Roadmap

### Frontend Tasks
- Implement "Book Now" section
- Improve Services section layout:
  - Reduce size of haircut boxes
  - Align and column layout (reference: https://voguevertu.it/servizi/)
  - Add image carousel for each haircut type
- Enhance Products section:
  - Add "View All" section for each product category
  - Add "View All" section for each haircut type
  - Expand product catalog with additional items

### Backend Tasks
- Set up database for users, permissions, appointment calendar, and shopping cart
- Implement authentication system
- Create API endpoints for appointment booking and product management

## Contributing
This project is part of the Web Technologies course at the University of Turin. Please follow the established code style and commit guidelines when contributing.