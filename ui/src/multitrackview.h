/*
  Q Light Controller Plus
  multitrackview.h

  Copyright (C) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef MULTITRACKVIEW_H
#define MULTITRACKVIEW_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QWidget>

#include "showitems.h"
#include "chaser.h"
#include "track.h"

/** @addtogroup ui_shows
 * @{
 */

class MultiTrackView : public QGraphicsView
{
    Q_OBJECT
    
public:
    MultiTrackView(QWidget *parent = 0);
    
    /** Update tracks horizontal dividers when the view changes */
    void updateTracksDividers();

    /** Set the multitrack view size in pixels */
    void setViewSize(int width, int height);

    /** Auto calculation of view size based on items */
    void updateViewSize();

    /*********************************************************************
     * Contents
     *********************************************************************/

    /** Update the multitrack view with the scene elements */
    void resetView();

    /** Add a new track to the view */
    void addTrack(Track *track);

    /** Add a new sequence item to the given track */
    void addSequence(Chaser *chaser);

    /** Add a new audio item to the given track */
    void addAudio(Audio *audio);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    /** Add a new video item to the given track */
    void addVideo(Video *video);
#endif

    /** Delete the currently selected sequence */
    quint32 deleteSelectedFunction();

    /** Set the given track to active state */
    void activateTrack(Track *track);

    /** get the selected sequence item. If none, returns NULL */
    SequenceItem *getSelectedSequence();

    /** get the selected audio item. If none, returns NULL */
    AudioItem *getSelectedAudio();

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    /** get the selected video item. If none, returns NULL */
    VideoItem *getSelectedVideo();
#endif

private:
    /** Get the index of the currently selected track */
    int getActiveTrack();

    /*********************************************************************
     * Header
     *********************************************************************/
public:
    /** Set the type of header. Can be Time (seconds) or BPM,
     *  in various forms (4/4, 3/4) */
    void setHeaderType(SceneHeaderItem::TimeDivision type);

    SceneHeaderItem::TimeDivision getHeaderType();

    /** When BPM is selected, this function can set a precise
     *  value of time division */
    void setBPMValue(int value);

    void setSnapToGrid(bool enable);

    /*********************************************************************
     * Cursor
     *********************************************************************/
public:
    /** Move cursor to a given time */
    void moveCursor(quint32 timePos);

    /** Reset cursor to initial position */
    void rewindCursor();

    /** Get time in milliseconds of the current cursor position */
    quint32 getTimeFromCursor();

private:

    /** Return position in pixel of a given time (in msec) */
    quint32 getPositionFromTime(quint32 time);

    /** Return the time (in msec) from a given X position */
    quint32 getTimeFromPosition(qreal pos);

    void updateItem(SequenceItem *, quint32 time);
    void updateItem(AudioItem *, quint32 time);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    void updateItem(VideoItem *, quint32 time);
#endif

private:
    QGraphicsScene *m_scene;
    QSlider *m_timeSlider;
    SceneHeaderItem *m_header;
    SceneCursorItem *m_cursor;
    QGraphicsItem * m_vdivider;
    QList <QGraphicsItem *> m_hdividers;
    QList <TrackItem *> m_tracks;
    QList <SequenceItem *> m_sequences;
    QList <AudioItem *> m_audio;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    QList <VideoItem *> m_videos;
#endif
    bool m_snapToGrid;

public slots:
    void mouseReleaseEvent(QMouseEvent * e);

protected slots:
    void slotHeaderClicked(QGraphicsSceneMouseEvent *event);
    void slotTimeScaleChanged(int val);
    void slotTrackClicked(TrackItem *track);
    void slotTrackDoubleClicked(TrackItem *track);
    void slotTrackSoloFlagChanged(TrackItem*, bool);
    void slotTrackMuteFlagChanged(TrackItem*, bool);
    void slotViewScrolled(int);

    void slotSequenceMoved(QGraphicsSceneMouseEvent *event, SequenceItem *);
    void slotSequenceMoved(QGraphicsSceneMouseEvent *, AudioItem *);
    void slotAlignToCursor(SequenceItem *);
    void slotAlignToCursor(AudioItem *);
#if QT_VERSION >= 0x050000
    void slotSequenceMoved(QGraphicsSceneMouseEvent *, VideoItem *);
    void slotAlignToCursor(VideoItem *);
#endif

signals:
    void sequenceMoved(SequenceItem *item, quint32 time, bool moved);
    void audioMoved(AudioItem *item);
#if QT_VERSION >= 0x050000
    void videoMoved(VideoItem *item);
#endif
    void viewClicked(QMouseEvent * e);
    void timeChanged(quint32 msec);
    void trackClicked(Track *track);
    void trackDoubleClicked(Track *track);
    void trackMoved(Track *, int);
    void trackDelete(Track *);
};

/** @} */

#endif
