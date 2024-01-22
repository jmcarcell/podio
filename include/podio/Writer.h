#ifndef PODIO_WRITER_H
#define PODIO_WRITER_H

#include "podio/Frame.h"
#include "podio/podioVersion.h"

namespace podio {

class Writer {
public:
  struct WriterConcept {
    virtual ~WriterConcept() = default;

    virtual void writeFrame(const podio::Frame& frame, const std::string& category) = 0;
    virtual void writeFrame(const podio::Frame& frame, const std::string& category,
                            const std::vector<std::string>& collections) = 0;
    virtual void writeEvent(const podio::Frame& frame) = 0;
    virtual void writeEvent(const podio::Frame& frame, const std::vector<std::string>& collections) = 0;
  };

  template <typename T>
  struct WriterModel : public WriterConcept {
    WriterModel(T* writer) : m_writer(writer) {
    }
    WriterModel(const WriterModel&) = delete;
    WriterModel& operator=(const WriterModel&) = delete;

    void writeFrame(const podio::Frame& frame, const std::string& category) override {
      return m_writer->writeFrame(frame, category);
    }
    void writeFrame(const podio::Frame& frame, const std::string& category,
                    const std::vector<std::string>& collections) override {
      return m_writer->writeFrame(frame, category, collections);
    }
    void writeEvent(const podio::Frame& frame) override {
      return writeFrame(frame, podio::Category::Event);
    }
    void writeEvent(const podio::Frame& frame, const std::vector<std::string>& collections) override {
      return writeFrame(frame, podio::Category::Event, collections);
    }
    std::unique_ptr<T> m_writer{nullptr};
  };

  std::unique_ptr<WriterConcept> m_self{nullptr};

  template <typename T>
  Writer(std::unique_ptr<T>);

  void writeFrame(const podio::Frame& frame, const std::string& category) {
    return m_self->writeFrame(frame, category);
  }
  void writeFrame(const podio::Frame& frame, const std::string& category, const std::vector<std::string>& collections) {
    return m_self->writeFrame(frame, category, collections);
  }
  void writeEvent(const podio::Frame& frame) {
    return writeFrame(frame, podio::Category::Event);
  }
  void writeEvent(const podio::Frame& frame, const std::vector<std::string>& collections) {
    return writeFrame(frame, podio::Category::Event, collections);
  }
};

std::unique_ptr<Writer> makeWriter(const std::string& filename, const std::string& type = "default");

} // namespace podio

#endif // PODIO_WRITER_H