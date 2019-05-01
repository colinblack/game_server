package ProtoBuilding {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBuilding.BuildUserSyncInfo;
	import ProtoBuilding.BuildQueue;
	import ProtoBuilding.BuildInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BuildSyncResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildSyncResp.type", "type", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type:uint;

		/**
		 *  @private
		 */
		public static const BUILDS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildSyncResp.builds", "builds", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildInfo; });

		[ArrayElementType("ProtoBuilding.BuildInfo")]
		public var builds:Array = [];

		/**
		 *  @private
		 */
		public static const QUEUE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildSyncResp.queue", "queue", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildQueue; });

		public var queue:ProtoBuilding.BuildQueue;

		/**
		 *  @private
		 */
		public static const USER:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildSyncResp.user", "user", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildUserSyncInfo; });

		public var user:ProtoBuilding.BuildUserSyncInfo;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type);
			for (var builds$index:uint = 0; builds$index < this.builds.length; ++builds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.builds[builds$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.queue);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.user);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var type$count:uint = 0;
			var queue$count:uint = 0;
			var user$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildSyncResp.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.builds.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBuilding.BuildInfo()));
					break;
				case 3:
					if (queue$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildSyncResp.queue cannot be set twice.');
					}
					++queue$count;
					this.queue = new ProtoBuilding.BuildQueue();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.queue);
					break;
				case 4:
					if (user$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildSyncResp.user cannot be set twice.');
					}
					++user$count;
					this.user = new ProtoBuilding.BuildUserSyncInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.user);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
