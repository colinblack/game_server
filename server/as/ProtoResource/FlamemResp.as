package ProtoResource {
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
	public dynamic final class FlamemResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.type", "type", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type:uint;

		/**
		 *  @private
		 */
		public static const MULTIPLE:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.multiple", "multiple", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var multiple:Array = [];

		/**
		 *  @private
		 */
		public static const VALUE:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoResource.FlamemResp.value", "value", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var value:UInt64;

		/**
		 *  @private
		 */
		public static const FREE_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.free_cnt", "freeCnt", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var freeCnt:uint;

		/**
		 *  @private
		 */
		public static const BUY_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.buy_cnt", "buyCnt", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var buyCnt:uint;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.cash", "cash", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const REWARDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoResource.FlamemResp.rewards", "rewards", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var rewards:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type);
			for (var multiple$index:uint = 0; multiple$index < this.multiple.length; ++multiple$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.multiple[multiple$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.value);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.freeCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.buyCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			for (var rewards$index:uint = 0; rewards$index < this.rewards.length; ++rewards$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewards[rewards$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var type$count:uint = 0;
			var value$count:uint = 0;
			var free_cnt$count:uint = 0;
			var buy_cnt$count:uint = 0;
			var cash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: FlamemResp.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.multiple);
						break;
					}
					this.multiple.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if (value$count != 0) {
						throw new flash.errors.IOError('Bad data format: FlamemResp.value cannot be set twice.');
					}
					++value$count;
					this.value = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 4:
					if (free_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: FlamemResp.freeCnt cannot be set twice.');
					}
					++free_cnt$count;
					this.freeCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (buy_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: FlamemResp.buyCnt cannot be set twice.');
					}
					++buy_cnt$count;
					this.buyCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: FlamemResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.rewards);
						break;
					}
					this.rewards.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
