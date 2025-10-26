#include <pda/hal/ARTCHAL.h>

class PaperS3RTCHAL: public ARTCHAL {
public:
    virtual ~PaperS3RTCHAL() = default;
    
    void init() override;
    DateTime getDateTime() override;
    void setDateTime(const DateTime& dt) override;
    void setAlarm(const DateTime& dt) override;
};