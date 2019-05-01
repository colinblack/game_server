package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBuilding.BuildQueue;
	import ProtoBuilding.BuildInfo;
	import ProtoBuilding.BuildYield;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Building extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const BUILDS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.Building.builds", "builds", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildInfo; });

		[ArrayElementType("ProtoBuilding.BuildInfo")]
		public var builds:Array = [];

		/**
		 *  @private
		 */
		public static const QUEUE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.Building.queue", "queue", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildQueue; });

		public var queue:ProtoBuilding.BuildQueue;

		/**
		 *  @private
		 */
		public static const YIELD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.Building.yield", "yield", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBuilding.BuildYield; });

		[ArrayElementType("ProtoBuilding.BuildYield")]
		public var yield:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var builds$index:uint = 0; builds$index < this.builds.length; ++builds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.builds[builds$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.queue);
			for (var yield$index:uint = 0; yield$index < this.yield.length; ++yield$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.yield[yield$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var queue$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.builds.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBuilding.BuildInfo()));
					break;
				case 2:
					if (queue$count != 0) {
						throw new flash.errors.IOError('Bad data format: Building.queue cannot be set twice.');
					}
					++queue$count;
					this.queue = new ProtoBuilding.BuildQueue();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.queue);
					break;
				case 3:
					this.yield.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBuilding.BuildYield()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
