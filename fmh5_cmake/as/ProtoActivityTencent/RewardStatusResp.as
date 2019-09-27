package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class RewardStatusResp
	{
		public static const PROTO:String = "ProtoActivityTencent.RewardStatusResp";
		public var package_root:*;
		public  var message:*;
		public var blueDaily:int;
		public var blueGrow:int;
		public var qqgamePrivilegeDaily:int;
		public var qqgamePrivilegeGrow:int;
		public function RewardStatusResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			blueDaily = undefined;
			blueGrow = undefined;
			qqgamePrivilegeDaily = undefined;
			qqgamePrivilegeGrow = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.blueDaily!= undefined)
			{
				serializeObj.blueDaily = this.blueDaily;
			}
			if(this.blueGrow!= undefined)
			{
				serializeObj.blueGrow = this.blueGrow;
			}
			if(this.qqgamePrivilegeDaily!= undefined)
			{
				serializeObj.qqgamePrivilegeDaily = this.qqgamePrivilegeDaily;
			}
			if(this.qqgamePrivilegeGrow!= undefined)
			{
				serializeObj.qqgamePrivilegeGrow = this.qqgamePrivilegeGrow;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardStatusResp
		{
			blueDaily = undefined;
			blueGrow = undefined;
			qqgamePrivilegeDaily = undefined;
			qqgamePrivilegeGrow = undefined;
			if(msgObj.hasOwnProperty("blueDaily"))
			{
				this.blueDaily = msgObj.blueDaily;
			}
			if(msgObj.hasOwnProperty("blueGrow"))
			{
				this.blueGrow = msgObj.blueGrow;
			}
			if(msgObj.hasOwnProperty("qqgamePrivilegeDaily"))
			{
				this.qqgamePrivilegeDaily = msgObj.qqgamePrivilegeDaily;
			}
			if(msgObj.hasOwnProperty("qqgamePrivilegeGrow"))
			{
				this.qqgamePrivilegeGrow = msgObj.qqgamePrivilegeGrow;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardStatusResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}