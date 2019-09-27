package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class RewardTaskResp
	{
		public static const PROTO:String = "ProtoTask.RewardTaskResp";
		public var package_root:*;
		public  var message:*;
		public var task:TaskCPP;
		public var commons:CommonItemsCPP;
		public function RewardTaskResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			task = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.task = this.task.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardTaskResp
		{
			task = undefined;
			commons = undefined;
			this.task = new TaskCPP(package_root).unserialize(msgObj.task);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardTaskResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}