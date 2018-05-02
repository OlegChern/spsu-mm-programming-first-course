package Host;

/**
 * @see ConnectionsService#performGreeting
 */
@FunctionalInterface
interface PerformGreeting {
    boolean greet(Connection newConnection);
}
