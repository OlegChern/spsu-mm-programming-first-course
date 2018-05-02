package Host;

/**
 * @see ConnectionsService#acceptGreeting
 */
@FunctionalInterface
interface AcceptGreeting {
    boolean answer(Connection newSubscriber);
}
