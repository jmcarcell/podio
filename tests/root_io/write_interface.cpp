#include "write_frame.h"

#include "podio/Writer.h"

void write_frames(std::unique_ptr<podio::Writer> frameWriter) {

  for (int i = 0; i < 10; ++i) {
    auto frame = makeFrame(i);
    frameWriter->writeFrame(frame, podio::Category::Event, collsToWrite);
  }

  for (int i = 100; i < 110; ++i) {
    auto frame = makeFrame(i);
    frameWriter->writeFrame(frame, "other_events");
  }
}

int main(int, char**) {

  auto writer = podio::makeWriter("example_frame_interface.root");
  write_frames(std::move(writer));

#ifdef PODIO_ENABLE_RNTUPLE
  auto writerRNTuple = podio::makeWriter("example_frame_rntuple_interface.root", "rntuple");
  write_frames(std::move(writerRNTuple));
#endif

#ifdef PODIO_ENABLE_SIO
  auto writerSIO = podio::makeWriter("example_frame_sio_interface.sio", "sio");
  write_frames(std::move(writerSIO));
#endif

  return 0;
}
