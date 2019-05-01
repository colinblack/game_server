package ProtoPush {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class TimesAddPushReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MISSION_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.TimesAddPushReq.mission_times", "missionTimes", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var mission_times$field:uint;

		private var hasField$0:uint = 0;

		public function clearMissionTimes():void {
			hasField$0 &= 0xfffffffe;
			mission_times$field = new uint();
		}

		public function get hasMissionTimes():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set missionTimes(value:uint):void {
			hasField$0 |= 0x1;
			mission_times$field = value;
		}

		public function get missionTimes():uint {
			return mission_times$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasMissionTimes) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, mission_times$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mission_times$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mission_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: TimesAddPushReq.missionTimes cannot be set twice.');
					}
					++mission_times$count;
					this.missionTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
