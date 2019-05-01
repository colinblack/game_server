package ProtoAchievement {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoAchievement.AchievementAllCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PushAchievementReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ACHIEVEMENTS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAchievement.PushAchievementReq.achievements", "achievements", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoAchievement.AchievementAllCPP; });

		public var achievements:ProtoAchievement.AchievementAllCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.achievements);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var achievements$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (achievements$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushAchievementReq.achievements cannot be set twice.');
					}
					++achievements$count;
					this.achievements = new ProtoAchievement.AchievementAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.achievements);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
