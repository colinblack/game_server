package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class SetFormationReq
	{
		public static const PROTO:String = "ProtoBattle.SetFormationReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:Vector.<int>;
		public function SetFormationReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = [];
			for(var i:int = 0;i < this.heroid.length;i++)
			{
				serializeObj.heroid.push(this.heroid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetFormationReq
		{
			heroid = new Vector.<int>();
			for(var i:int = 0;i < msgObj.heroid.length;i++)
			{
				this.heroid.push(msgObj.heroid[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetFormationReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}