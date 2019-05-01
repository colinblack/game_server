package ProtoMine {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineRecord extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const OPERATE:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoMine.MineRecord.operate", "operate", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var operate:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const TARGET:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoMine.MineRecord.target", "target", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var target:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const OP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineRecord.op", "op", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var op:uint;

		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineRecord.type", "type", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type:uint;

		/**
		 *  @private
		 */
		public static const PARAMS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoMine.MineRecord.params", "params", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var params:Array = [];

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineRecord.ts", "ts", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.operate);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.target);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.op);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type);
			for (var params$index:uint = 0; params$index < this.params.length; ++params$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.params[params$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var operate$count:uint = 0;
			var target$count:uint = 0;
			var op$count:uint = 0;
			var type$count:uint = 0;
			var ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (operate$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineRecord.operate cannot be set twice.');
					}
					++operate$count;
					this.operate = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 2:
					if (target$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineRecord.target cannot be set twice.');
					}
					++target$count;
					this.target = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 3:
					if (op$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineRecord.op cannot be set twice.');
					}
					++op$count;
					this.op = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineRecord.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.params);
						break;
					}
					this.params.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 6:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineRecord.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
