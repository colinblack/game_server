package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivityAllCPP
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivityAllCPP";
		public var package_root:*;
		public  var message:*;
		public var activities:Vector.<GameAcitivityCPP>;
		public function GameAcitivityAllCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			activities = new Vector.<GameAcitivityCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.activities = [];
			for(var i:int = 0;i < this.activities.length;i++)
			{
				serializeObj.activities.push(this.activities[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GameAcitivityAllCPP
		{
			activities = new Vector.<GameAcitivityCPP>();
			for(var i:int = 0;i < msgObj.activities.length;i++)
			{
				this.activities.push(new GameAcitivityCPP(package_root).unserialize(msgObj.activities[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivityAllCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}