package ProtoModelTrial {
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
	public dynamic final class ModelTrialCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CURPOS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoModelTrial.ModelTrialCPP.curpos", "curpos", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var curpos:uint;

		/**
		 *  @private
		 */
		public static const FIGHT_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoModelTrial.ModelTrialCPP.fight_times", "fightTimes", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var fightTimes:uint;

		/**
		 *  @private
		 */
		public static const BUY_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoModelTrial.ModelTrialCPP.buy_times", "buyTimes", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var buyTimes:uint;

		/**
		 *  @private
		 */
		public static const RESETTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoModelTrial.ModelTrialCPP.resetts", "resetts", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var resetts:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.curpos);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.fightTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.buyTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.resetts);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var curpos$count:uint = 0;
			var fight_times$count:uint = 0;
			var buy_times$count:uint = 0;
			var resetts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (curpos$count != 0) {
						throw new flash.errors.IOError('Bad data format: ModelTrialCPP.curpos cannot be set twice.');
					}
					++curpos$count;
					this.curpos = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (fight_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ModelTrialCPP.fightTimes cannot be set twice.');
					}
					++fight_times$count;
					this.fightTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (buy_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ModelTrialCPP.buyTimes cannot be set twice.');
					}
					++buy_times$count;
					this.buyTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (resetts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ModelTrialCPP.resetts cannot be set twice.');
					}
					++resetts$count;
					this.resetts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
