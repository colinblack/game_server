package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class GetTaskResp
	{
		public static const PROTO:String = "ProtoTask.GetTaskResp";
		public var package_root:*;
		public  var message:*;
		public var task:Vector.<TaskCPP>;
		public function GetTaskResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			task = new Vector.<TaskCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.task = [];
			for(var i:int = 0;i < this.task.length;i++)
			{
				serializeObj.task.push(this.task[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetTaskResp
		{
			task = new Vector.<TaskCPP>();
			for(var i:int = 0;i < msgObj.task.length;i++)
			{
				this.task.push(new TaskCPP(package_root).unserialize(msgObj.task[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetTaskResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}