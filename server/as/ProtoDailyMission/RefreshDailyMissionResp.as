package ProtoDailyMission {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoDailyMission.DailyMissionAllCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class RefreshDailyMissionResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MISSIONALL:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoDailyMission.RefreshDailyMissionResp.missionall", "missionall", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoDailyMission.DailyMissionAllCPP; });

		public var missionall:ProtoDailyMission.DailyMissionAllCPP;

		/**
		 *  @private
		 */
		public static const REFRESHTIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.RefreshDailyMissionResp.refreshtime", "refreshtime", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refreshtime:uint;

		/**
		 *  @private
		 */
		public static const FREETIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.RefreshDailyMissionResp.freetimes", "freetimes", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var freetimes:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.missionall);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refreshtime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.freetimes);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var missionall$count:uint = 0;
			var refreshtime$count:uint = 0;
			var freetimes$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (missionall$count != 0) {
						throw new flash.errors.IOError('Bad data format: RefreshDailyMissionResp.missionall cannot be set twice.');
					}
					++missionall$count;
					this.missionall = new ProtoDailyMission.DailyMissionAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.missionall);
					break;
				case 2:
					if (refreshtime$count != 0) {
						throw new flash.errors.IOError('Bad data format: RefreshDailyMissionResp.refreshtime cannot be set twice.');
					}
					++refreshtime$count;
					this.refreshtime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (freetimes$count != 0) {
						throw new flash.errors.IOError('Bad data format: RefreshDailyMissionResp.freetimes cannot be set twice.');
					}
					++freetimes$count;
					this.freetimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
