import React from 'react';

interface ErrorMessageProps {
  message: string;
  className?: string;
}

const ErrorMessage: React.FC<ErrorMessageProps> = ({ message, className = '' }) => {
  if (!message) return null;

  return (
    <div className={`error-message text-danger mt-2 ${className}`}>
      {message}
    </div>
  );
};

export default ErrorMessage;