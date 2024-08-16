const std = @import("std");

const capacity = 1_000_000;
const maxNumber = 1_000;
const experiments = 1_000;

const TestData = struct {
    data: []u32,
    target: u32,
};

fn testInit(allocator: *std.mem.Allocator) !TestData {
    const testData = TestData{
        .data = try allocator.alloc(u32, capacity),
        .target = 2 * maxNumber + 1,
    };

    var prng = std.rand.DefaultPrng.init(9847576489578);
    const rand = prng.random();

    for (testData.data) |*elem| {
        elem.* = rand.intRangeAtMost(u32, 0, maxNumber);
    }

    return testData;
}

fn testRun(testData: TestData) !void {
    var seen = std.AutoHashMap(u32, bool).init(std.heap.page_allocator);

    defer seen.deinit();

    for (testData.data) |value| {
        const searchFor = testData.target - value;
        if (seen.contains(searchFor)) {
            return error.UnexpectedCondition;
        }

        try seen.put(value, true);
    }
}

pub fn main() !void {
    var best: f128 = std.math.floatMax(f128);

    for (experiments) |_| {
        var allocator = std.heap.page_allocator;
        const data = testInit(&allocator) catch unreachable;

        const start = std.time.nanoTimestamp();
        try testRun(data);
        const end = std.time.nanoTimestamp();

        const duration = @as(f128, @floatFromInt(end - start)) / 1e6;
        best = if (duration < best) duration else best;

        std.debug.print("\r{d:.6}\n", .{best});

        allocator.free(data.data);
    }
}
