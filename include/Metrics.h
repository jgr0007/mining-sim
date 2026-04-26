#ifndef METRICS_H
#define METRICS_H

// Requirement: "Calculate and report statistics for the performance and efficiency of each mining truck and unload station."
// So I'm deciding whats important myself.
struct StationMetrics {
    int time_utilized{0};
    int time_idle{0};
    int longest_unload_line{0};
    int trucks_unloaded{0};
};

struct TruckMetrics {
    int time_mining{0};
    int time_traveling{0};
    int time_waiting{0};
};

#endif // METRICS_H