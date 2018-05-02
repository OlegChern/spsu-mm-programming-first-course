package Host;

/**
 * @see ConnectionsService#onConnectionServiceClosure
 */
@FunctionalInterface
interface OnConnectionServiceClosure {
    void performLastAction(Connection closingConnection);
}
