import React, { ReactNode } from 'react';
import { Modal as BootstrapModal, Button } from 'react-bootstrap';

interface PopupProps {
  isOpen: boolean;
  onClose: () => void;
  title: string;
  children: ReactNode;
  footer?: ReactNode;
}

const Popup: React.FC<PopupProps> = ({ isOpen, onClose, title, children, footer }) => {
  return (
    <BootstrapModal show={isOpen} onHide={onClose} centered>
      <BootstrapModal.Header closeButton>
        <BootstrapModal.Title>{title}</BootstrapModal.Title>
      </BootstrapModal.Header>
      <BootstrapModal.Body>{children}</BootstrapModal.Body>
      {footer && <BootstrapModal.Footer>{footer}</BootstrapModal.Footer>}
    </BootstrapModal>
  );
};

export default Popup;