package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.OpenPlatformRewardConfigCPP;
	import ProtoNPCActivity.ActivityAffairConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class NPCActivityConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ACTIVITY_AFFAIRS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.NPCActivityConfigCPP.activity_affairs", "activityAffairs", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.ActivityAffairConfigCPP; });

		[ArrayElementType("ProtoNPCActivity.ActivityAffairConfigCPP")]
		public var activityAffairs:Array = [];

		/**
		 *  @private
		 */
		public static const OPEN_PLATFORM_REWARD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.NPCActivityConfigCPP.open_platform_reward", "openPlatformReward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.OpenPlatformRewardConfigCPP; });

		[ArrayElementType("ProtoNPCActivity.OpenPlatformRewardConfigCPP")]
		public var openPlatformReward:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var activityAffairs$index:uint = 0; activityAffairs$index < this.activityAffairs.length; ++activityAffairs$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.activityAffairs[activityAffairs$index]);
			}
			for (var openPlatformReward$index:uint = 0; openPlatformReward$index < this.openPlatformReward.length; ++openPlatformReward$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.openPlatformReward[openPlatformReward$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.activityAffairs.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.ActivityAffairConfigCPP()));
					break;
				case 2:
					this.openPlatformReward.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.OpenPlatformRewardConfigCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
