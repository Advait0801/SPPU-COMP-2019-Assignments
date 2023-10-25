class Router:
    def __init__(self, name):
        self.name = name
        self.routing_table = {}  # {destination: (next_hop, cost)}

    def update_routing_table(self, destination, next_hop, cost):
        if destination not in self.routing_table or cost < self.routing_table[destination][1]:
            self.routing_table[destination] = (next_hop, cost)

class Network:
    def __init__(self):
        self.routers = {}

    def add_router(self, router):
        self.routers[router.name] = router

    def send_routing_updates(self):
        for router_name, router in self.routers.items():
            for neighbor_name, neighbor in self.routers.items():
                if router_name != neighbor_name:
                    for destination, (next_hop, cost) in neighbor.routing_table.items():
                        if destination not in router.routing_table:
                            router.update_routing_table(destination, neighbor_name, cost + 1)
                        else:
                            if cost + 1 < router.routing_table[destination][1]:
                                router.update_routing_table(destination, neighbor_name, cost + 1)

    def print_routing_tables(self):
        for router_name, router in self.routers.items():
            print(f"Routing table for {router_name}:")
            print("Destination\tNext Hop\tCost")
            for destination, (next_hop, cost) in router.routing_table.items():
                print(f"{destination}\t\t{next_hop}\t\t{cost}")
            print("\n")


A = Router('A')
B = Router('B')
C = Router('C')
network = Network()
network.add_router(A)
network.add_router(B)
network.add_router(C)
A.update_routing_table('A', 'A', 0)
B.update_routing_table('B', 'B', 0)
C.update_routing_table('C', 'C', 0)
network.send_routing_updates()
network.print_routing_tables()
