package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class TaskCPP
	{
		public static const PROTO:String = "ProtoTask.TaskCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var curtaskvalue:int;
		public var curtaskstar:int;
		public var rewardstatus:int;
		public function TaskCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			curtaskvalue = undefined;
			curtaskstar = undefined;
			rewardstatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.curtaskvalue = this.curtaskvalue;
			serializeObj.curtaskstar = this.curtaskstar;
			serializeObj.rewardstatus = this.rewardstatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):TaskCPP
		{
			id = undefined;
			curtaskvalue = undefined;
			curtaskstar = undefined;
			rewardstatus = undefined;
			this.id = msgObj.id;
			this.curtaskvalue = msgObj.curtaskvalue;
			this.curtaskstar = msgObj.curtaskstar;
			this.rewardstatus = msgObj.rewardstatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TaskCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}