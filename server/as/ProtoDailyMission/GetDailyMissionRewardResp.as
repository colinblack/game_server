package ProtoDailyMission {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoDailyMission.DailyMissionCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetDailyMissionRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MISSION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoDailyMission.GetDailyMissionRewardResp.mission", "mission", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoDailyMission.DailyMissionCPP; });

		public var mission:ProtoDailyMission.DailyMissionCPP;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoDailyMission.GetDailyMissionRewardResp.exp", "exp", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const REWARD_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoDailyMission.GetDailyMissionRewardResp.reward_times", "rewardTimes", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardTimes:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mission);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewardTimes);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mission$count:uint = 0;
			var exp$count:uint = 0;
			var reward_times$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mission$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetDailyMissionRewardResp.mission cannot be set twice.');
					}
					++mission$count;
					this.mission = new ProtoDailyMission.DailyMissionCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.mission);
					break;
				case 2:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetDailyMissionRewardResp.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 3:
					if (reward_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetDailyMissionRewardResp.rewardTimes cannot be set twice.');
					}
					++reward_times$count;
					this.rewardTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
