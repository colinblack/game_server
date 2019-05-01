package ProtoBuilding {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBuilding.BuildQueue;
	import ProtoBuilding.BuildUserSyncInfo;
	import ProtoBuilding.BuildInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BuildUpgradeResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUpgradeResp.id", "id", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var id:uint;

		/**
		 *  @private
		 */
		public static const USER:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildUpgradeResp.user", "user", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildUserSyncInfo; });

		public var user:ProtoBuilding.BuildUserSyncInfo;

		/**
		 *  @private
		 */
		public static const BUILD_QUEUE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildUpgradeResp.build_queue", "buildQueue", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildQueue; });

		public var buildQueue:ProtoBuilding.BuildQueue;

		/**
		 *  @private
		 */
		public static const BUILDS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBuilding.BuildUpgradeResp.builds", "builds", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildInfo; });

		[ArrayElementType("ProtoBuilding.BuildInfo")]
		public var builds:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.user);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.buildQueue);
			for (var builds$index:uint = 0; builds$index < this.builds.length; ++builds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.builds[builds$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var id$count:uint = 0;
			var user$count:uint = 0;
			var build_queue$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (id$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUpgradeResp.id cannot be set twice.');
					}
					++id$count;
					this.id = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (user$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUpgradeResp.user cannot be set twice.');
					}
					++user$count;
					this.user = new ProtoBuilding.BuildUserSyncInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.user);
					break;
				case 3:
					if (build_queue$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUpgradeResp.buildQueue cannot be set twice.');
					}
					++build_queue$count;
					this.buildQueue = new ProtoBuilding.BuildQueue();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.buildQueue);
					break;
				case 4:
					this.builds.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBuilding.BuildInfo()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
