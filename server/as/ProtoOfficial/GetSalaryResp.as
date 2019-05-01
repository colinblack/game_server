package ProtoOfficial {
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
	public dynamic final class GetSalaryResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const SALARY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.GetSalaryResp.salary", "salary", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var salary:uint;

		/**
		 *  @private
		 */
		public static const COINS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.GetSalaryResp.coins", "coins", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coins:uint;

		/**
		 *  @private
		 */
		public static const JOB_REWARD_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.GetSalaryResp.job_reward_ts", "jobRewardTs", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var jobRewardTs:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.salary);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coins);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.jobRewardTs);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var salary$count:uint = 0;
			var coins$count:uint = 0;
			var job_reward_ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (salary$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetSalaryResp.salary cannot be set twice.');
					}
					++salary$count;
					this.salary = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (coins$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetSalaryResp.coins cannot be set twice.');
					}
					++coins$count;
					this.coins = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (job_reward_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetSalaryResp.jobRewardTs cannot be set twice.');
					}
					++job_reward_ts$count;
					this.jobRewardTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
